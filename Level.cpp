/*
 * Level.cpp
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <fstream>
#include <string>

#include "Level.h"

#include "entities/Ground.h"
#include "entities/Player.h"

/*Level::Level() {
	// TODO Auto-generated constructor stub

}*/

Level::~Level() {
	SDL_DestroyTexture(textures["ground"]);
}

void Level::load_from_file(int const& level)
{
	//Loads a level from a file line by line and adds it to the grounds vector.
	std::map<std::string, char> objects{{"ground", '#'}, {"player", 'p'}};

	std::ifstream file("levels/level1.txt");
	std::string line;
	int current_line{0};

	while(getline(file, line))
	{
		for (unsigned int i{0}; i < line.length(); ++i)
		{
			if (line[i] == objects["ground"])
			{
				grounds.push_back(new Ground(50,50,(i*50),(current_line*50),textures["ground"]));
			}

			if (line[i] == objects["player"])
			{
				player = new Player(50 ,50 , i*50, current_line*50,textures["player"]);
			}
		}
		++current_line;
	}
}

void Level::initialize_level(int level)
{
	SDL_Surface* temp = IMG_Load("textures/wall.png");
	textures["ground"] = SDL_CreateTextureFromSurface(renderer, temp);

	temp = IMG_Load("textures/player.png");
	textures["player"] = SDL_CreateTextureFromSurface(renderer, temp);

	load_from_file(3);
	SDL_FreeSurface(temp);

}


void Level::draw_level(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
	SDL_RenderClear(renderer);

	for (Ground* g : grounds)
	{
		g->draw_texture(renderer);
	}
	player->draw_texture(renderer);

	SDL_RenderPresent(renderer);
}

void Level::update_level()
{
	player->update_movement(grounds);
}

Player*& Level::get_player()
{
	return player;
}
