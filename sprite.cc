#include "sprite.h"

sprite::sprite( SDL_Renderer * r) {
  myPosition    = vector2< float >( 0, 0 );
  myDimensions  = vector2< int >( 0, 0 );
  myRotation    = 0.;
  myScaleFactor = 1.;

  myRenderer = r;

  SDL_Surface* image = IMG_Load( "sprite.png" );
  if( image == NULL ) std::cout << "Error loading image: " << IMG_GetError() << std::endl;
  texture = SDL_CreateTextureFromSurface( myRenderer, image );
  if(texture == NULL) std::cout << "create surface failed " << SDL_GetError() << std::endl;
  SDL_QueryTexture( texture, NULL, NULL, &myDimensions.values[ 0 ], &myDimensions.values[ 1 ] );
}

void sprite::draw(){
  // if( texture == nullptr ) std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;

  SDL_Rect whereToDraw;
  int w = myDimensions.values[ 0 ] * myScaleFactor;
  int h = myDimensions.values[ 1 ] * myScaleFactor;

  // doing it this way, so that we are placing by the centerpoint
  whereToDraw.x = int( myPosition.values[ 0 ] ) - ( w / 2 ); // x
  whereToDraw.y = int( myPosition.values[ 1 ] ) - ( h / 2 ); // y
  whereToDraw.w = w;
  whereToDraw.h = h;

  // SDL_RenderCopy( myRenderer, texture, NULL, &whereToDraw );
  SDL_RenderCopyEx( myRenderer, texture, NULL, &whereToDraw, myRotation, NULL, SDL_FLIP_NONE );
}

sprite::~sprite(){
  SDL_DestroyTexture( texture );
}
