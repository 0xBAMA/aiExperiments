#include "application.h"

app::app( int argc, char** argv ) {
  // SDL init
  SDL_Init( SDL_INIT_EVERYTHING );
  window = SDL_CreateWindow( windowTitle, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
  renderer = SDL_CreateRenderer( window, -1, 0 );

  // create the track
  myTrack = new track( renderer );

  init();
}

void app::init(){
  agents.clear();
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution< int > jiggle( -25, 25 );

  if( parents.size() == 0 ){
    for( int i = 0; i < numAgents; i++ ){
      agent a( myTrack, renderer, 0.1618f, 0.0f, vector2< float >( 100 + jiggle( gen ), 100 - jiggle( gen ) ) );
      agents.push_back( a );
    }
  }else{
    std::uniform_int_distribution< int > pick( 0, parents.size() - 1 );
    for( int i = 0; i < numAgents; i++ ){
      agent a( myTrack, renderer, 0.1618f, 0.0f, vector2< float >( 100 + jiggle( gen ), 100 - jiggle( gen ) ) );
      a.setBrain( parents[ pick( gen ) ].getBrain() );
      a.bumpBrain( 0.5f );
      agents.push_back( a );
    }
  }
}

bool app::mainLoop(){
  // approximately equal to the number of ms since initialization
  // int time = SDL_GetTicks();

  // pause function, prevents the agent update function from running
  static bool runSim = false;

  // clear framebuffer to opaque black
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderClear( renderer );

  // draw the background - this is the grayscale track distance representation
  myTrack->draw();

  // iterate through list of agents, and draw their associated sprites
  for( auto& agent : agents ){
    if( runSim ){
      agent.raymarchDistances();
      agent.update();
    }
    agent.draw();
  }
  std::cout << std::flush;

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

    // hit r to run the simulation again, with the selected parents used to spawn the next generation
    if( event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r ){

      parents.clear();

      // put all selected agents into the parent vector
      for( auto& agent : agents )
        if( agent.isSelected() )
          parents.push_back( agent );

      std::cout << "starting next run of " << numAgents << " agents ( " << parents.size() << " parents )" << std::endl;

      init();  // call init() to spawn a new set of simulation agents, with the selected parents
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
