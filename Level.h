/*
 * Level.h
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_LEVEL_H_
#define ENTITIES_LEVEL_H_

#include <vector>
#include <map>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Abstract_Gamestate.h"
#include "entities/Ground.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Bullet.h"
#include "entities/Button.h"
#include "entities/Wall_Of_Death.h"
#include "entities/Shooting_Enemy.h"
#include "entities/Lava.h"

class Level {
public:
	Level(SDL_Renderer& renderer, int level_to_load, Abstract_Gamestate::Gamestate & CurrentState) :
		screen_width{640}, screen_height{480}, renderer(renderer), camera{0,0, screen_width, screen_height}, player{nullptr},
		button{nullptr}, CAMERA_MAX_SPEED{4}, CAMERA_SPEEDUP_TIMER{900}, game_paused{false}, menu_opened{false},
		selected_button{0}, current_level{level_to_load}, level_cleared{false}, CurrentState{CurrentState} {}
	virtual ~Level();

	void initialize_level();
	void update_level();
	void draw_level(SDL_Renderer& renderer);

	void game_menu();

	void pause_game();

	void change_selection(int change);
	void execute_selection();

	void display_message(std::string message, SDL_Rect display_pos);

	int get_current_level() const { return current_level; }
	bool get_level_cleared() const { return level_cleared; }
	Player*& get_player() { return player; }


private:
	void update_camera();
	void update_camera_speed();

	void load_from_file();

	int screen_width;
	int screen_height;

	std::vector<Enemy*> enemies;
	SDL_Renderer& renderer;

	SDL_Rect camera;
	std::vector<Ground*> grounds;
	Player* player;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Rect> button_rects;
	Button* button;

	const int CAMERA_MAX_SPEED;
	const int CAMERA_SPEEDUP_TIMER;
	int camera_speed {1};
	int camera_counter{0};

	bool game_paused;
	bool menu_opened;

	int selected_button;

	int current_level;
	bool level_cleared;

	Abstract_Gamestate::Gamestate & CurrentState;


};

#endif /* ENTITIES_LEVEL_H_ */
