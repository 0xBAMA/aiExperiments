#include "track.h"

track::track( SDL_Renderer* r ) : myRenderer( r ) {
  // populate the array of primitives - this defines the shape of the track
    // this is totally arbitrary - start with random circles
  std::vector< SDFBase* > primitives;

  primitives.push_back( new circle( vector2< float >( windowWidth / 2., windowHeight / 4. ), 150., false ) );
  primitives.push_back( new lineSegment( vector2< float >( 100., 100. ), vector2< float >( windowWidth - 100., 100. ), 100., false ) );
  primitives.push_back( new lineSegment( vector2< float >( windowWidth - 100., 100. ), vector2< float >( windowWidth - 100., windowHeight - 100 ), 100., false ) );
  primitives.push_back( new lineSegment( vector2< float >( windowWidth - 100., windowHeight - 100 ), vector2< float >( 100., windowHeight - 100 ), 100., false ) );
  primitives.push_back( new lineSegment( vector2< float >( 100., windowHeight - 100 ), vector2< float >( 100., 100. ), 100., false ) );

  // produce the float array of distance values, to cache distance for all points on the map
  for( int x = 0; x < windowWidth;  x++ )
  for( int y = 0; y < windowHeight; y++ ){
    distanceMap[ x ][ y ] = 10000.0f;
    for( auto primitive : primitives ) {  // compose all the primiives with the min() operator
      distanceMap[ x ][ y ] = std::min( primitive->distance( vector2< float >( x, y ) ), distanceMap[ x ][ y ] );
    }
  }

  // destroy the SDFs, as they are no longer needed
  for( auto& entry : primitives ) delete entry;

  // create the texture, for the SDL renderer display
  myTexture = SDL_CreateTexture( myRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STATIC, windowWidth, windowHeight );

  // create the texture data
  std::vector< unsigned char > v;
  for( int y = 0; y < windowHeight; y++ )
  for( int x = 0; x < windowWidth;  x++ )
  for( int c = 0; c < 4; c++) // same data for all 4 color channels
    v.push_back( static_cast< unsigned char >( std::clamp( dQuery( vector2< float >( x, y ) ), 0.0f, 255.0f ) ) );

  // put it in the newly created texture
  SDL_UpdateTexture( myTexture, NULL, &v[ 0 ], 4 * windowWidth );
}

bool oob( vector2< float > p ){
  return ( p.values[ 0 ] < 0 || p.values[ 0 ] > windowWidth - 1 || p.values[ 1 ] < 0 || p.values[ 1 ] > windowHeight - 1 );
}

float track::dQuery( vector2< float > queryPoint ){
  if( oob( queryPoint ) ) return 0;
  return -distanceMap[ int( queryPoint.values[ 0 ] ) ][ int( queryPoint.values[ 1 ] ) ];
}

void track::draw(){
  // use myRenderer to draw myTexture
  SDL_Rect whereToDraw = { 0, 0, windowWidth, windowHeight };
  SDL_RenderCopy( myRenderer, myTexture, NULL, &whereToDraw );
}

track::~track(){
  // destroy the texture
  SDL_DestroyTexture( myTexture );
}
