#include "vector.h"

#define unixcheck (!defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))))
#if unixcheck
  #include <SDL2/SDL.h>
#else
  #include <SDL.h>
#endif

class sprite{
public:
  sprite();
  ~sprite();

  void setPosition( vector2< int > newPos ) { position = newPos; }
  void setRotation( float newRot )          { rotation = newRot; }

  void loadFromFile( std::string fileName );
  void draw( SDL_Renderer* renderer );

private:
  // sprite parameters
  vector2< int > position;
  vector2< int > dimensions;

  float rotation; // degrees/radians tbd

  // sprite contents - populated by stb_image
  SDL_Surface* data;
};
