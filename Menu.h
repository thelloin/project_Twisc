/*
 * Menu.h
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */

#ifndef MENU_H_
#define MENU_H_

#include "Abstract_Gamestate.h"
#include <SDL2/SDL.h>

class Menu : public Abstract_Gamestate{
public:
	Menu();
	virtual ~Menu();

	Abstract_Gamestate::Gamestate run_screen(SDL_Renderer* renderer);

protected:
	void initialize(SDL_Renderer* renderer);
	void handle_input();
	void updateAll();
	void drawAll(SDL_Renderer* renderer);

	void load_texture(SDL_Texture* & texture_to_load, std::string path, SDL_Renderer* renderer);

private:
	SDL_Texture* menu_test;
	//Abstract_Gamestate::Gamestate Menustate {Gamestate::Menu};
};

#endif /* MENU_H_ */
