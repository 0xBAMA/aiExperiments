#include "application.h"

app::app( int argc, char** argv ) {
  SDL_Init( SDL_INIT_EVERYTHING );
  window = SDL_CreateWindow( windowTitle, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
  renderer = SDL_CreateRenderer( window, -1, 0 );

  myTrack = new track( renderer );

  // seeding the PRNG
  std::random_device rd;
  std::mt19937 gen(rd());

  // distributions for the PRNG
  std::uniform_real_distribution< float > scalarDistribution( 0.01, 1. );
  std::uniform_real_distribution< float > rotationDistribution( 0., 360. );
  std::uniform_int_distribution< int > positionXDist( 0, windowWidth );
  std::uniform_int_distribution< int > positionYDist( 0, windowHeight );

  // create a vector of sprites and randomize the render parameters
  agents.resize( numAgents );
  for( auto& agent : agents ) {
    // agent's sprites have a pointer to the renderer
    agent.mySprite.setRenderer( renderer );

    // this now sets the base dimensions, directly from the texture data
    agent.mySprite.loadFromFile( "sprite.png" );

    // randomly sized, randomly rotated, randomly positioned
    agent.mySprite.setScaleFactor( scalarDistribution( gen ) );
    agent.mySprite.setRotation( rotationDistribution( gen ) );
    agent.mySprite.setPosition( vector2< int >( positionXDist( gen ), positionYDist( gen ) ) );
  }
}

bool app::mainLoop(){
  int time = SDL_GetTicks(); // approximately equal to the number of ms since initialization

  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  myTrack->draw();

  for( auto& agent : agents ){
    agent.mySprite.draw();
    agent.mySprite.setRotation( time * 0.1 );
  }

  SDL_RenderPresent( renderer );
  return time < runTime; // break after you see the time exceed runTime
}


app::~app(){
  agents.clear();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
