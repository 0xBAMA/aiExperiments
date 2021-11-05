
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

    std::default_random_engine generator;
    std::uniform_int_distribution<int> dimensionDistribution( 100, 200 );
    std::uniform_int_distribution<int> rotationDistribution( 0, 360 );
    std::uniform_int_distribution<int> positionDistributionX( 0, windowWidth );
    std::uniform_int_distribution<int> positionDistributionY( 0, windowHeight );

    s.resize( 5 );
    for( auto& sprite : s ){
      sprite.setRenderer( renderer );
      sprite.loadFromFile( "sprite.png" );

      // square, of random edge length - randomly rotated, randomly positioned
      sprite.setDimensions( vector2< int >( dimensionDistribution( generator ) ) );
      sprite.setRotation( rotationDistribution( generator ) );
      sprite.setPosition( vector2< int >( positionDistributionX( generator ), positionDistributionY( generator ) ) );
    }
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

    for( auto& sprite : s )
      sprite.draw();

    SDL_RenderPresent( renderer );
    return time < runTime; // break after you see the time exceed runTime
  }

  private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector< sprite > s;
  };

int main( int argc, char** argv ) {
  app application( argc, argv );

  while( application.mainLoop() ) {
    // nothing, yet
  }

  return 0;
}
