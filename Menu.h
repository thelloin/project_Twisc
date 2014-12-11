/*
 * Menu.h
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */

#ifndef MENU_H_
#define MENU_H_

#include "Abstract_Gamestate.h"
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Menu : public Abstract_Gamestate{
public:
	Menu() : selected_button{0} {}
	virtual ~Menu();

	Abstract_Gamestate::Gamestate run_screen(SDL_Renderer& renderer);

protected:
	void initialize(SDL_Renderer& renderer);
	void handle_input();
	void updateAll();
	void drawAll(SDL_Renderer& renderer);


private:
	int selected_button;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Rect> rects;

	void change_selection();
	void execute_selection();
};

#endif /* MENU_H_ */
