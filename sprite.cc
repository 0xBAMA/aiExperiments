#include <iostream>
#include "sprite.h"

sprite::sprite() {
    position = vector2< int >(0, 0);
    dimensions = vector2< int >(0, 0);
    rotation = 0;
}

void sprite::loadFromFile( std::string fileName ) {
    image = IMG_Load("sprite.png");
    if (image == NULL) std::cout << "Error loading image: " << IMG_GetError() << std::endl;
    texture = SDL_CreateTextureFromSurface(myRenderer, image);
}


void sprite::draw(){
    if (texture == nullptr) std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_RenderCopy(myRenderer, texture, NULL, NULL);
}


sprite::~sprite(){
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(image);
}
