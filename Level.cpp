/*
 * Level.cpp
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */
#include "Level.h"
#include "iostream"


Level::~Level() {
	SDL_DestroyTexture(textures["ground"]);
	SDL_DestroyTexture(textures["player"]);
	SDL_DestroyTexture(textures["bullet"]);
	SDL_DestroyTexture(textures["lava"]);
	SDL_DestroyTexture(textures["wall_of_death"]);
	SDL_DestroyTexture(textures["continue_button"]);
	SDL_DestroyTexture(textures["go_to_button"]);
	SDL_DestroyTexture(textures["die_message"]);
	SDL_DestroyTexture(textures["level_cleared_message"]);
	SDL_DestroyTexture(textures["powerup_message"]);
	SDL_DestroyTexture(textures["game_beaten_message"]);
	SDL_DestroyTexture(textures["shooting_enemy"]);
	SDL_DestroyTexture(textures["button"]);




	delete player;
	delete button;

	for (unsigned int i{0}; i < grounds.size(); i++)
	{
		delete grounds[i];
		grounds[i] = nullptr;
	}
	for (unsigned int i{0}; i < enemies.size(); i++)
	{
		delete enemies[i];
		enemies[i] = nullptr;
	}
}

void Level::load_from_file()
{

	//Loads a level from a file line by line and adds it to the
	//different vectors that contains the objects in the world
	std::map<std::string, char> objects{{"ground", '#'}, {"player", 'p'}, {"shooting_enemy", 's'}, {"lava", 'l'},
	{"button", 'b'}};

	std::string level_str = "levels/level" + std::to_string(current_level) + ".txt";
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
	file.close();

}

void Level::initialize_level()
{


	// Loads the game_beaten-message
	SDL_Surface* temp = IMG_Load("textures/game_beaten_message.png");
	textures["game_beaten_message"] = SDL_CreateTextureFromSurface(&renderer,temp);
	SDL_FreeSurface(temp);


	//Draw the Winningscreen and go back to the menu
	if (current_level == 4)
	{
		SDL_RenderClear(&renderer);
		SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
		SDL_Rect temp_rect = {320 - 150,180,300,100};
		display_message("game_beaten_message", temp_rect);
		SDL_Delay(2000);
		CurrentState = Abstract_Gamestate::Menu;
		return;
	}

	temp = IMG_Load("textures/wall.png");
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

	// Loads the death-message
	temp = IMG_Load("textures/die_message.png");
	textures["die_message"] = SDL_CreateTextureFromSurface(&renderer,temp);
	SDL_FreeSurface(temp);

	// Loads the level_cleared-message
	temp = IMG_Load("textures/level_cleared_message.png");
	textures["level_cleared_message"] = SDL_CreateTextureFromSurface(&renderer,temp);
	SDL_FreeSurface(temp);

	// Loads the powerup-message
	temp = IMG_Load("textures/powerup_message.png");
	textures["powerup_message"] = SDL_CreateTextureFromSurface(&renderer,temp);
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

	if (player->get_has_powerup() == true)
	{
		SDL_Rect temp_rect{320 - 150, 20, 300, 100};
		display_message("powerup_message", temp_rect);
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
			if (enemies[i]->is_within_screen(camera))
			{
				enemies[i]->update_movement();
			}
			Bullet* bullet = dynamic_cast<Bullet*>(enemies[i]);
			if (bullet != nullptr && bullet->is_destroyed())
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}

		level_cleared = player->button_pushed(button);
		update_camera();
		update_camera_speed();
	}
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

void Level::display_message(std::string message, SDL_Rect display_pos)
{
	//Display a message to the screen
	SDL_RenderCopy(&renderer, textures[message], nullptr , &display_pos);
	SDL_RenderPresent(&renderer);
}

void Level::update_camera_speed()
{
	++camera_counter;
	if (camera_counter >= CAMERA_SPEEDUP_TIMER && camera_speed < CAMERA_MAX_SPEED)
	{
		++camera_speed;
		camera_counter = 0;
		for (Enemy* enemy: enemies)
		{
			Wall_Of_Death* wall_of_death = dynamic_cast<Wall_Of_Death*>(enemy);
			if (wall_of_death != nullptr)
			{
				wall_of_death->set_wall_speed(camera_speed);
			}
		}
	}
}



