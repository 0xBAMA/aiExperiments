#include "agent.h"


#include <random>
#include <iostream>
std::string randomString( std::size_t length ){
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;
    for( std::size_t i = 0; i < length; ++i ){
      random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

agent::agent( std::string filename, track* t, SDL_Renderer* r, float scale, float rot, vector2< int >location ){
  mySprite.setRenderer( r );
  mySprite.loadFromFile( filename );
  mySprite.setScaleFactor( scale );
  mySprite.setRotation( rot );
  mySprite.setPosition( location );

  tag = randomString( 10 );

  setTrack( t );
}

void agent::update(){
  if( dead ) return;
  updatesSurvived++;

  mySprite.setPosition( mySprite.getPosition() + speed * rotate2D( vector2< float >( 1, 0), mySprite.getDirection() ) );

  if( myD <= 0.){
    dead = true; // forever die, forever fly
    brain.saveWeightsToFile( std::string( "records/" ) + std::to_string( updatesSurvived ) + std::string( "_" ) + tag );
  }
}

void agent::draw(){
  SDL_Renderer * r = mySprite.getRenderer();

  // do some lines
  vector2< float > agentPosition = vector2< float >( float( mySprite.getPosition().values[ 0 ] ), float( mySprite.getPosition().values[ 1 ] ) );
  float agentDirection = mySprite.getRotation();
  vector2< float > directionVector = rotate2D( vector2< float >( 1, 0 ), agentDirection );

  // makes the below easier to reference
  int sx = agentPosition.values[ 0 ];
  int sy = agentPosition.values[ 1 ];

  // draw the forwards vector
  int dx = int( ( agentPosition + zero * directionVector ).values[ 0 ] );
  int dy = int( ( agentPosition + zero * directionVector ).values[ 1 ] );
  SDL_SetRenderDrawColor( r, 255, 255, 255, 255 );
  SDL_RenderDrawLine( r, sx, sy, dx, dy );
  SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
  // SDL_RenderDrawPoint( r, dx, dy );
  SDL_Rect drawRect = { dx - 2, dy - 2, 4, 4 };
  SDL_RenderDrawRect( r, &drawRect );


  // draw the +/- 45 degree lines
  vector2< float > plus45 = rotate2D( directionVector, 45 ), minus45 = rotate2D( directionVector, -45 );
  SDL_SetRenderDrawColor( r, 127, 127, 127, 255 );
  dx = int( ( agentPosition + p45 * plus45  ).values[ 0 ] );
  dy = int( ( agentPosition + p45 * plus45  ).values[ 1 ] );
  SDL_RenderDrawLine( r, sx, sy, dx, dy);
  SDL_SetRenderDrawColor( r, 255, 0, 0, 255 ); // mark the endpoint
  drawRect = { dx - 2, dy - 2, 4, 4 };
  SDL_RenderDrawRect( r, &drawRect );

  SDL_SetRenderDrawColor( r, 127, 127, 127, 255 );
  dx = int( ( agentPosition + m45 * minus45  ).values[ 0 ] );
  dy = int( ( agentPosition + m45 * minus45  ).values[ 1 ] );
  SDL_RenderDrawLine( r, sx, sy, dx, dy );
  SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
  drawRect = { dx - 2, dy - 2, 4, 4 };
  SDL_RenderDrawRect( r, &drawRect );

  // draw the +/- 90 degree lines
  vector2< float > plus90 = rotate2D( directionVector, 90 ), minus90 = rotate2D( directionVector, -90 );
  SDL_SetRenderDrawColor( r, 64, 64, 64, 255 );
  dx = int( ( agentPosition + p90 * plus90  ).values[ 0 ] );
  dy = int( ( agentPosition + p90 * plus90  ).values[ 1 ] );
  SDL_RenderDrawLine( r, sx, sy, dx, dy );
  SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
  drawRect = { dx - 2, dy - 2, 4, 4 };
  SDL_RenderDrawRect( r, &drawRect );

  SDL_SetRenderDrawColor( r, 64, 64, 64, 255 );
  dx = int( ( agentPosition + m90 * minus90 ).values[ 0 ] );
  dy = int( ( agentPosition + m90 * minus90 ).values[ 1 ] );
  SDL_RenderDrawLine( r, sx, sy, dx, dy );
  SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
  drawRect = { dx - 2, dy - 2, 4, 4 };
  SDL_RenderDrawRect( r, &drawRect );

  if( selected ){
    drawRect = { sx - 10, sy - 10, 20, 20 };
    SDL_SetRenderDrawColor( r, 255, 0, 0, 255 );
    SDL_RenderDrawRect( r, &drawRect );
    mySprite.setScaleFactor( 0.2617f );
  }else{
    mySprite.setScaleFactor( 0.1618f );
  }

  // draw the sprite over the lines
  mySprite.draw();
}

float agent::raymarchVector( vector2< float > origin, vector2< float > direction ){
  float distance = 0., t = 0.;
  for( int i = 0; i < 10; i++ ){
    distance = myTrack->dQuery( origin + t * direction );
    t += distance;
    if( t > 1000. || distance < 0. )
      break;
  }
  return std::max( t, 0.0f );
}

void agent::raymarchDistances(){
  vector2< float > origin = vector2< float >( mySprite.getPosition().values[ 0 ], mySprite.getPosition().values[ 1 ] );
  vector2< float > direction = rotate2D( vector2< float >( 1, 0 ), mySprite.getRotation() );

  myD = myTrack->dQuery( origin );

  m90  = raymarchVector( origin, normalize( rotate2D( direction, -90 ) ) );
  m45  = raymarchVector( origin, normalize( rotate2D( direction, -45 ) ) );
  zero = raymarchVector( origin, normalize( direction ) );
  p45  = raymarchVector( origin, normalize( rotate2D( direction,  45 ) ) );
  p90  = raymarchVector( origin, normalize( rotate2D( direction,  90 ) ) );
}
