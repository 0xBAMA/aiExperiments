#include <iostream>
#include "sprite.h"
#include <SDL_image.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

sprite::sprite() {
    position = vector2< int >(0, 0);
    dimensions = vector2< int >(0, 0);
    rotation = 0;

}

void sprite::loadFromFile(std::string fileName, SDL_Renderer* renderer) {
    image = IMG_Load("sprite.png");
    if (image == NULL) {
        std::cout << "Error loading image: " << IMG_GetError();
    }
    texture = SDL_CreateTextureFromSurface(renderer, image);
}


void sprite::draw(SDL_Renderer* renderer) {

    // SDL_FreeSurface( data ); // need to hold a texture instead of a surface

    if (texture == nullptr) {
        std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    }

    SDL_RenderCopy(renderer, texture, NULL, NULL);
}


sprite::~sprite() {
   // SDL_FreeSurface(data);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}
