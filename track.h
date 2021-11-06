#ifndef TRACK
#define TRACK

#include "windowDefines.h"
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
  float dQuery()
}

#endif
