/*
 * Level.cpp
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Level.h"
#include "Ground.h"

Level::Level() {
	// TODO Auto-generated constructor stub

}

Level::~Level() {
	// TODO Auto-generated destructor stub
}


void Level::initialize_level(int level)
{
	SDL_Surface* temp = IMG_Load("");
	SDL_Texture* texture_to_load = SDL_CreateTextureFromSurface(nullptr, temp);
	grounds.push_back(new Ground(0,0,0,0,texture_to_load));
	SDL_FreeSurface(temp);

}
