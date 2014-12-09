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
#include "Abstract_Gamestate.h"

#include "entities/Ground.h"
#include "entities/Player.h"
#include "entities/Shooting_Enemy.h"
#include "entities/Wall_Of_Death.h"
#include "entities/Lava.h"
#include "entities/Enemy.h"

/*Level::Level() {
	// TODO Auto-generated constructor stub

}*/

Level::~Level() {
	SDL_DestroyTexture(textures["ground"]);
	SDL_DestroyTexture(textures["player"]);
	SDL_DestroyTexture(textures["bullet"]);
	SDL_DestroyTexture(textures["lava"]);
	SDL_DestroyTexture(textures["wall_of_death"]);
	SDL_DestroyTexture(textures["continue_button"]);
	SDL_DestroyTexture(textures["go_to_button"]);


	delete player;

	for (unsigned int i{0}; i < grounds.size(); i++)
	{
		delete grounds[i];
	}
	for (int i{0}; i < enemies.size(); i++)
	{
		std::cout << "borttagen" << std::endl;
		delete enemies[i];
	}


}

void Level::load_from_file()
{

	//Loads a level from a file line by line and adds it to the
	//different vectors that contains the objects in the world
	std::map<std::string, char> objects{{"ground", '#'}, {"player", 'p'}, {"shooting_enemy", 's'}, {"lava", 'l'},
	{"button", 'b'}};

	std::string level_str = "levels/level" + std::to_string(current_level) + ".txt";
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
				grounds.push_back(new Ground(80,80,(i*80),(current_line*80),*textures["ground"]));
			}

			if (line[i] == objects["player"])
			{
				player = new Player(20 ,50 , i*80, current_line*80, *textures["player"]);
			}

			if (line[i] == objects["shooting_enemy"])
			{
				enemies.push_back(new Shooting_Enemy(80,80,(i*80),(current_line*80),
						*textures["shooting_enemy"], enemies, *textures["bullet"]));
			}
			if (line[i] == objects["lava"])
			{
				enemies.push_back(new Lava(80,80,(i*80),(current_line*80), *textures["lava"]));
			}
			if (line[i] == objects["button"])
			{
				button = new Button(20 ,80 , i*80 + 60, current_line*80, *textures["button"]);
				//enemies.push_back(new Lava(80,80,(i*80),(current_line*80), *textures["lava"]));
			}

		}
		++current_line;
	}

}

void Level::initialize_level()
{
	if (current_level == 4)
	{
		CurrentState = Abstract_Gamestate::Menu;
		return;
	}
	SDL_Surface* temp = IMG_Load("textures/wall.png");
	textures["ground"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/player.png");
	textures["player"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/shooting_enemy.png");
	textures["shooting_enemy"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/bullet.png");
	textures["bullet"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/lava.png");
	textures["lava"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/continue_button.png");
	textures["continue_button"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_Rect temp_rect {200,200, temp->w / 2 + 20, temp->h / 2 + 20};
	button_rects["continue_button"] = temp_rect;
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/go_to_button.png");
	textures["go_to_button"] = SDL_CreateTextureFromSurface(&renderer, temp);
	temp_rect = {170,300, temp->w / 2, temp->h / 2};
	button_rects["go_to_button"] = temp_rect;
	SDL_FreeSurface(temp);


	// Add the button-texture to the level
	temp = IMG_Load("textures/button.png");
	textures["button"] = SDL_CreateTextureFromSurface(&renderer,temp);

	load_from_file();

	// Add the wall-texture to the level
	temp = IMG_Load("textures/wall_of_death.png");
	textures["wall_of_death"] = SDL_CreateTextureFromSurface(&renderer,temp);
	enemies.push_back(new Wall_Of_Death(500,800,-400,0,
							*textures["wall_of_death"], camera_speed));
	SDL_FreeSurface(temp);

}


void Level::draw_level(SDL_Renderer& renderer)
{
	if (game_paused == false)
	{
		SDL_SetRenderDrawColor(&renderer, 183, 7, 61, 255);
		SDL_RenderClear(&renderer);

		for (Ground*& g : grounds)
		{
			g->draw_texture(renderer, camera_speed, camera.y);
		}

		for (Enemy*& e : enemies)
		{
			e->draw_texture(renderer, camera_speed, camera.y);
		}

		player->draw_texture(renderer, camera_speed, camera.y);

		button->draw_texture(renderer, camera_speed, camera.y);


		SDL_RenderPresent(&renderer);
	}
	else if(menu_opened == true)
	{
		SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
		SDL_RenderClear(&renderer);

		SDL_RenderCopy(&renderer, textures["continue_button"], nullptr, &button_rects["continue_button"]);
		SDL_RenderCopy(&renderer, textures["go_to_button"], nullptr, &button_rects["go_to_button"]);


		SDL_RenderPresent(&renderer);
	}
}

void Level::update_level()
{
	if (game_paused == false)
	{
		player->handle_collisions(enemies, button);

		player->update_movement(grounds);

		for (unsigned int i{0}; i < enemies.size(); ++i)
		{
			enemies[i]->update_movement();
			Bullet* bullet = dynamic_cast<Bullet*>(enemies[i]);
			if (bullet != nullptr && bullet->is_destroyed())
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}

		level_cleared = player->button_pushed(button);
		update_camera();
	}

}

Player*& Level::get_player()
{
	return player;
}

void Level::update_camera()
{
	if ((button->get_rect().x - camera.x) < 520)
	{
		camera.x += camera_speed;
		camera_speed = 0;
	}
	camera.y = player->get_rect().y - 240;
}

void Level::pause_game()
{
	if (menu_opened == false)
	{
		game_paused = !game_paused;
	}
}

void Level::game_menu()
{
	if ((menu_opened == true && game_paused == true)
			|| (menu_opened == false && game_paused == false))
	{
		menu_opened = !menu_opened;
		game_paused = !game_paused;
	}
}

void Level::change_selection(int change)
{
	if (menu_opened == true)
	{
		selected_button += change;
		//Makes the selection "loop"
		if (selected_button > 1)
		{
			selected_button = 0;
		}

		if (selected_button < 0)
		{
			selected_button = 1;
		}
		//Changed the rectangles size if selected
		if (selected_button == 0)
		{
			button_rects["continue_button"].w += 20;
			button_rects["continue_button"].h += 20;
			button_rects["go_to_button"].w -= 20;
			button_rects["go_to_button"].h -= 20;
		}

		if (selected_button == 1)
		{
			button_rects["continue_button"].w -= 20;
			button_rects["continue_button"].h -= 20;
			button_rects["go_to_button"].w += 20;
			button_rects["go_to_button"].h += 20;
		}
	}
}

void Level::execute_selection()
{
	if (selected_button == 0)
	{
		game_menu();
	}
	if (selected_button == 1)
	{
		CurrentState = Abstract_Gamestate::Gamestate::Menu;
	}
}

void Level::death_message()
{
	//Tells the player about his/her death
	SDL_Rect a = {0,0,100,100};
	SDL_RenderCopy(&renderer, textures["player"], nullptr , &a);
	SDL_RenderPresent(&renderer);
}



