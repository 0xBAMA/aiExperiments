#ifndef SPRITE
#define SPRITE

#include "vector.h"
#include <iostream>

#define unixcheck (!defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))))
#if unixcheck
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include <SDL.h>
  #include <SDL_image.h>
#endif
#undef unixcheck

class sprite {
public:
	sprite();
	~sprite();

	void setPosition( vector2< int > newPos )   { myPosition    = newPos;    }
	void setRotation( float newRot )            { myRotation    = newRot;    }
  void setDimensions( vector2< int > newDim ) { myDimensions  = newDim;    }
  void setScaleFactor( float newScalar )      { myScaleFactor = newScalar; }
  void setRenderer( SDL_Renderer* renderer )  { myRenderer    = renderer;  }

  SDL_Renderer* getRenderer()  { return myRenderer; }
  vector2< int > getPosition() { return myPosition; }
  float getRotation()          { return myRotation; }

	void loadFromFile( std::string fileName );
	void draw();

private:
	// sprite parameters
	vector2< int > myPosition;    // location of center
	vector2< int > myDimensions; // load from texture
	float myRotation;           // units are degrees
  float myScaleFactor;       // uniform scaling on x and y

  SDL_Renderer* myRenderer;
	SDL_Texture* texture;
};

#endif
