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
  std::uniform_real_distribution< float > scalarDist( 0.01, 1. );
  std::uniform_real_distribution< float > rotationDist( 0.0, 360.0 );
  std::uniform_real_distribution< float > positionXDist( 0, float( windowWidth ) );
  std::uniform_real_distribution< float > positionYDist( 0, float( windowHeight ) );

  for( int i = 0; i < numAgents; i++ ){
    agent a( myTrack, renderer, 0.1618f, rotationDist( gen ), vector2< float >( positionXDist( gen ), positionYDist( gen ) ) );
    agents.push_back(a);
  }
}

bool app::mainLoop(){
  // approximately equal to the number of ms since initialization
  // int time = SDL_GetTicks();

  // pause function, prevents the agent update function from running
  static bool runSim = true;

  // clear framebuffer to opaque black
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // draw the background - this is the grayscale track distance representation
  myTrack->draw();

  // iterate through list of agents, and draw their associated sprites
  for( auto& agent : agents ){
    if( runSim ){
      // agent.mySprite.setRotation( time * 0.1 );
      agent.rotationAdjust( 0.01 );
      agent.raymarchDistances();
      agent.update();
    }
    agent.draw();
  }

  // present the accumulated state of the renderer to the viewer
  SDL_RenderPresent( renderer );

  // iterate through the current queue of events
  SDL_Event event;
  while( SDL_PollEvent( &event ) ){
    if( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE )
      return false; // terminate on release of escape key

    if( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE )
      runSim = !runSim;

    // picking
    if( event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT ){
      // find the nearest agent to the mouse location
      // toggle the selection state of the nearest agent, if it's within a threshold
      vector2< float >clickPos( event.button.x, event.button.y );
      float minDistance = 10000.0f;
      int pick = -1;
      for( unsigned int i = 0; i < agents.size(); i++ ) {
        float d = len( agents[ i ].getPosition() - clickPos );
        if( d < minDistance ){
          minDistance = d;
          pick = i;
        }
      }
      if( minDistance < 16 && pick >= 0 ){
        agents[ pick ].toggleSelected();
      }
    }
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
