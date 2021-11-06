#ifndef APPLICATION
#define APPLICATION

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
#include "agent.h"
#include "track.h"

// window dimensions, etc
#include "windowDefines.h"

class app {
public:
  app( int argc, char** argv );
  ~app();

  bool mainLoop();

private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  std::vector< agent > agents;
  track* myTrack = NULL;
};


#endif
