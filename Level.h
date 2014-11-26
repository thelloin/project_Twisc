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

class Level {
public:
	Level(SDL_Renderer* renderer) : renderer(renderer) {}
	virtual ~Level();

	void initialize_level(int level);
	void update_level();
	void draw_level(SDL_Renderer* renderer);

private:
	//Player player;
	//vector<Monsters> monsters;
	//vector<bullets> bullets;
	SDL_Renderer* renderer;
	std::vector<Ground*> grounds;
	std::map<std::string, SDL_Texture*> textures;
};

#endif /* ENTITIES_LEVEL_H_ */