
#define unixcheck !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))

#if unixcheck
  #include <SDL2/SDL.h>
#else
  #include <SDL.h>
#endif

#undef unixcheck



#include <cmath>

#include "vector.h"
#include "sprite.h"

// window dimensions, etc
#include "windowDefines.h"

class app {
public:
  app(int argc, char** argv) {
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow( windowTitle, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, 0 );

    s.setRenderer( renderer );
    s.loadFromFile( "sprite.png" );
  }

  ~app() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  bool mainLoop() {
    int time = SDL_GetTicks(); // approximately equal to the number of ms since initialization

    SDL_SetRenderDrawColor( renderer, 0, 128 * std::sin( time / 100 ) + 128, 0, 255 );
    SDL_RenderClear( renderer );
    s.draw();
    SDL_RenderPresent( renderer );

    return time < runTime; // break after you see the time exceed runTime
  }

  private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  sprite s;
  };

int main( int argc, char** argv ) {
  app application( argc, argv );

  while( application.mainLoop() ) {
    // nothing, yet
  }

  return 0;
}
