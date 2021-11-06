#ifndef TRACK
#define TRACK

#include "windowDefines.h"
#include <vector>
#include "vector.h"
#include "SDFs.h"

#define unixcheck (!defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))))
#if unixcheck
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include <SDL.h>
  #include <SDL_image.h>
#endif
#undef unixcheck

class track{
public:
  track();
  ~track();

  void draw();
  float dQuery(); // to check distance - this will be used in the 2D raymarch

private:
  std::vector< SDF > primitives;
  float distanceMap[ windowWidth ][ windowHeight ];
  SDL_Texture * dTexture;
}

#endif
