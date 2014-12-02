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
#include "entities/Shooting_Enemy.h"

/*Level::Level() {
	// TODO Auto-generated constructor stub

}*/

Level::~Level() {
	SDL_DestroyTexture(textures["ground"]);
	SDL_DestroyTexture(textures["player"]);

	delete player;
	for (Ground* g: grounds)
	{
		delete g;
	}
	std::cout << "hej" << std::endl;


}

void Level::load_from_file(int const& level)
{
	//Loads a level from a file line by line and adds it to the grounds vector.
	std::map<std::string, char> objects{{"ground", '#'}, {"player", 'p'}, {"shooting_enemy", 's'}};

	std::string level_str = "levels/level" + std::to_string(level) + ".txt";
	std::cout << level_str << std::endl;
	std::ifstream file(level_str);
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
				player = new Player(30 ,30 , i*50, current_line*50,textures["player"]);
			}

			if (line[i] == objects["shooting_enemy"])
			{
				enemies.push_back(new Shooting_Enemy(50,50,(i*50),(current_line*50),textures["shooting_enemy"]));
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

	temp = IMG_Load("textures/shooting_enemy.png");
	textures["shooting_enemy"] = SDL_CreateTextureFromSurface(renderer, temp);

	temp = IMG_Load("textures/bullet.png");
	textures["bullet"] = SDL_CreateTextureFromSurface(renderer, temp);

	load_from_file(level);
	SDL_FreeSurface(temp);

}


void Level::draw_level(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 183, 7, 61, 255);
	SDL_RenderClear(renderer);

	for (Ground* g : grounds)
	{
		g->draw_texture(renderer, camera_speed);
	}

	for (Enemy* e : enemies)
	{
		e->draw_texture(renderer, camera_speed);
	}
	player->draw_texture(renderer, camera_speed);

	SDL_RenderPresent(renderer);
}

void Level::update_level()
{
	player->handle_collisions(enemies);

	player->update_movement(grounds);

	update_camera();


}

Player*& Level::get_player()
{
	return player;
}

void Level::update_camera()
{
	camera.x -= camera_speed;
}
