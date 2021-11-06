#ifndef TRACK
#define TRACK

#include "windowDefines.h"
#include <vector>
#include "vector.h"
#include "SDF.h"

#define unixcheck (!defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))))
#if unixcheck
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include <SDL.h>
  #include <SDL_image.h>
#endif
#undef unixcheck

class track {
public:
  track( SDL_Renderer* r );
  ~track();

  float dQuery( vector2< float > queryPoint );
  void draw();

private:
  SDL_Texture * myTexture;
  SDL_Renderer * myRenderer;

  std::vector< SDFBase > primitives;
  float distanceMap[ windowWidth ][ windowHeight ];
};

#endif
