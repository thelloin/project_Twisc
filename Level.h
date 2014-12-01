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
#include <SDL2/SDL.h>

#include "entities/Ground.h"
#include "entities/Player.h"

class Level {
public:
	Level(SDL_Renderer* renderer) : renderer(renderer), screen_width(640),
		screen_height(480), camera{0,0, screen_width, screen_height} {}
	virtual ~Level();

	void initialize_level(int level);

	void update_level();
	void update_camera();

	void draw_level(SDL_Renderer* renderer);
	void load_from_file(int const& level);

	Player*& get_player();
private:
	int screen_width;
	int screen_height;
	//Player player;
	//vector<Monsters> monsters;
	//vector<bullets> bullets;
	SDL_Renderer* renderer;

	SDL_Rect camera;
	std::vector<Ground*> grounds;
	Player* player;
	std::map<std::string, SDL_Texture*> textures;

	const double camera_speed {1};
	double camera_counter{0};
};

#endif /* ENTITIES_LEVEL_H_ */
