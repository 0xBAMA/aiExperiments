#include <iostream>
#include "sprite.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

sprite::sprite(){
  position   = vector2< int >( 0, 0 );
  dimensions = vector2< int >( 0, 0 );
  rotation   = 0;

}

void sprite::loadFromFile( std::string fileName ){

  int channels;
  unsigned char * load = stbi_load( fileName.c_str(), &dimensions.values[ 0 ], &dimensions.values[ 1 ], &channels, 3 );

  if( load == NULL ) {
    SDL_Log( "Loading image failed: %s", stbi_failure_reason() );
    // exit( 1 );
  }

  data = SDL_CreateRGBSurfaceFrom( ( void* ) data, dimensions.values[ 0 ], dimensions.values[ 1 ], 24, 3 * dimensions.values[ 0 ], 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff );

  stbi_image_free( load );
}


void sprite::draw( SDL_Renderer* renderer ){
  SDL_Texture *texture = SDL_CreateTextureFromSurface( renderer, data );

  // SDL_FreeSurface( data ); // need to hold a texture instead of a surface

  if( texture == nullptr ){
    std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
  }

  SDL_RenderCopy( renderer, texture, NULL, NULL ); // Copy the texture into render
}


sprite::~sprite(){
  SDL_FreeSurface( data );
}
