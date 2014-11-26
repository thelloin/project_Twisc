/*
 * Level.cpp
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "Level.h"
#include "entities/Ground.h"

/*Level::Level() {
	// TODO Auto-generated constructor stub

}*/

Level::~Level() {
	SDL_DestroyTexture(textures["ground"]);
}


void Level::initialize_level(int level)
{
	SDL_Surface* temp = IMG_Load("textures/wall.png");
	textures["ground"] = SDL_CreateTextureFromSurface(renderer, temp);

	grounds.push_back(new Ground(temp->w,temp->h,100,350,textures["ground"]));
	grounds.push_back(new Ground(50,50,100,300,textures["ground"]));
	grounds.push_back(new Ground(50,50,500,350,textures["ground"]));
	grounds.push_back(new Ground(50,50,500,300,textures["ground"]));
	grounds.push_back(new Ground(50,50,500,250,textures["ground"]));

	SDL_FreeSurface(temp);

}


void Level::draw_level(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);

	for (Ground* g : grounds)
	{
		g->draw_texture(renderer);
	}

	SDL_RenderPresent(renderer);
}

