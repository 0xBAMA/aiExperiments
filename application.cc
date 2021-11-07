#include "application.h"

app::app( int argc, char** argv ) {
  // SDL init
  SDL_Init( SDL_INIT_EVERYTHING );
  window = SDL_CreateWindow( windowTitle, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
  renderer = SDL_CreateRenderer( window, -1, 0 );

  // create the track
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
    // pass reference to the track, so that the sim agent can reference it
    agent.setTrack( myTrack );

    // agent's sprites have a pointer to the renderer
    agent.mySprite.setRenderer( renderer );

    // this now sets the base dimensions, directly from the texture data
    agent.mySprite.loadFromFile( "sprite.png" );

    // randomly sized, randomly rotated, randomly positioned
    agent.mySprite.setScaleFactor( 0.1618f );
    agent.mySprite.setRotation( rotationDistribution( gen ) );
    agent.mySprite.setPosition( vector2< int >( positionXDist( gen ), positionYDist( gen ) ) );
  }
}

bool app::mainLoop(){
  // approximately equal to the number of ms since initialization
  int time = SDL_GetTicks();

  // clear framebuffer to opaque black
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // draw the background - this is the grayscale track distance representation
  myTrack->draw();

  // iterate through list of agents, and draw their associated sprites
  for( auto& agent : agents ){
    // agent.mySprite.draw();
    agent.raymarchDistances();
    agent.draw();
    agent.mySprite.setRotation( time * 0.1 );
  }

  // present the accumulated state of the renderer to the viewer
  SDL_RenderPresent( renderer );

  // iterate through the current queue of events
  SDL_Event event;
  while( SDL_PollEvent( &event ) ){
    if( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
      return false; // terminate on release of escape key
  }

  // if you fall through the event loop, continue
  return true;
}


app::~app(){
  // blow away simulation agents
  agents.clear();

  // SDL shutdown
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
