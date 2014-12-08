/*
 * Play_Screen.h
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */

#ifndef PLAY_SCREEN_H_
#define PLAY_SCREEN_H_

#include <SDL2/SDL.h>

#include "Abstract_Gamestate.h"
#include "Level.h"

class Play_Screen : public Abstract_Gamestate {
public:
	Play_Screen(SDL_Renderer& renderer) : level_to_load(1), renderer(renderer), max_level(4) {}
	virtual ~Play_Screen();

	Abstract_Gamestate::Gamestate run_screen(SDL_Renderer& renderer);

protected:
	void initialize(SDL_Renderer& renderer);
	void handle_input();
	void updateAll();
	void drawAll(SDL_Renderer& renderer);


private:
	//SDL_Texture* play_test;
	Level* level;
	int level_to_load;
	const int max_level;

	SDL_Renderer& renderer;

	void restart_level();
	void next_level();


};

#endif /* PLAY_SCREEN_H_ */
