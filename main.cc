
#define unixcheck (!defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))))
#if unixcheck
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include <SDL.h>
  #include <SDL_image.h>
#endif
#undef unixcheck


#include <cmath>

#include "vector.h"
#include "sprite.h"
#include "track.h"

// window dimensions, etc
#include "windowDefines.h"

class app {
public:
  app( int argc, char** argv ){
    SDL_Init( SDL_INIT_EVERYTHING );
    window = SDL_CreateWindow( windowTitle, 0, 0, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
    renderer = SDL_CreateRenderer( window, -1, 0 );

    t = new track( renderer );

    // seeding the PRNG
    std::random_device rd;
    std::mt19937 gen(rd());

    // distributions for the PRNG
    std::uniform_real_distribution< float > scalarDistribution( 0.01, 1. );
    std::uniform_real_distribution< float > rotationDistribution( 0., 360. );
    std::uniform_int_distribution< int > positionXDist( 0, windowWidth );
    std::uniform_int_distribution< int > positionYDist( 0, windowHeight );

    // create a vector of sprites and randomize the render parameters
    s.resize( numSprites );
    for( auto& sprite : s ){
      // sprites now have a pointer to the renderer
      sprite.setRenderer( renderer );

      // this now sets the base dimensions, directly from the texture data
      sprite.loadFromFile( "sprite.png" );

      // randomly sized, randomly rotated, randomly positioned
      sprite.setScaleFactor( scalarDistribution( gen ) );
      sprite.setRotation( rotationDistribution( gen ) );
      sprite.setPosition( vector2< int >( positionXDist( gen ), positionYDist( gen ) ) );
    }
  }

  ~app() {
    s.clear();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  bool mainLoop() {
    int time = SDL_GetTicks(); // approximately equal to the number of ms since initialization

    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );

    t->draw();

    for( auto& sprite : s ){
      sprite.draw();
      sprite.setRotation( time * 0.1 );
    }

    SDL_RenderPresent( renderer );
    return time < runTime; // break after you see the time exceed runTime
  }

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector< sprite > s;
  track* t = NULL;
};

int main( int argc, char** argv ){
  app application( argc, argv );

  while( application.mainLoop() ){
    // nothing, yet
  }

  return 0;
}
