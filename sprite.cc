#include "sprite.h"

sprite::sprite() {
  myPosition   = vector2< int >(100, 100);
  myDimensions = vector2< int >(50, 50);
  myRotation   = 30;
}

void sprite::loadFromFile( std::string fileName ) {
  SDL_Surface* image = IMG_Load( "sprite.png" );
  if( image == NULL ) std::cout << "Error loading image: " << IMG_GetError() << std::endl;
  texture = SDL_CreateTextureFromSurface( myRenderer, image );
}


void sprite::draw(){
  if( texture == nullptr ) std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;

  SDL_Rect whereToDraw;
  whereToDraw.x = myPosition.values[ 0 ];     // x
  whereToDraw.y = myPosition.values[ 1 ];     // y
  whereToDraw.w = myDimensions.values[ 0 ];
  whereToDraw.h = myDimensions.values[ 1 ];

  // SDL_RenderCopy( myRenderer, texture, NULL, &whereToDraw );
  SDL_RenderCopyEx( myRenderer, texture, NULL, &whereToDraw, myRotation, NULL, SDL_FLIP_NONE );
}


sprite::~sprite(){
  SDL_DestroyTexture( texture );
}
