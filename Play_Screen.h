/*
 * Play_Screen.h
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */

#ifndef PLAY_SCREEN_H_
#define PLAY_SCREEN_H_

#include "Abstract_Gamestate.h"
#include <SDL2/SDL.h>

class Play_Screen : public Abstract_Gamestate {
public:
	Play_Screen();
	virtual ~Play_Screen();

	//enum Gamestate{Menu, Playstate, Gameover, Exit, None};

	Abstract_Gamestate::Gamestate run_screen(SDL_Renderer* renderer);

protected:
	void initialize(SDL_Renderer* renderer);
	void handle_input();
	void updateAll();
	void drawAll(SDL_Renderer* renderer);

	SDL_Texture* load_texture(SDL_Texture* & texture_to_load, std::string path, SDL_Renderer* renderer);

private:
	SDL_Texture* play_test;
};

#endif /* PLAY_SCREEN_H_ */
