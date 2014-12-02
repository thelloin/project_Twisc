/*
 * Menu.cpp
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Menu.h"

Menu::Menu() {
	// TODO Auto-generated constructor stub

}

Menu::~Menu() {
	// TODO Auto-generated destructor stub
	SDL_DestroyTexture(menu_test);
}

Abstract_Gamestate::Gamestate Menu::run_screen(SDL_Renderer* renderer) {
	Currentstate = Gamestate::Menu;
	Menu::initialize(renderer);
	while (Currentstate == Gamestate::Menu) {
		// T
		Uint32 ticksAtLoopStart = SDL_GetTicks();

		Menu::handle_input();
		//GameScreen::updateAll();
		Menu::drawAll(renderer);

		// T
		//int time_to_wait = ticksPerFrame
		//                            - (SDL_GetTicks() - ticksAtLoopStart);
		//if (time_to_wait > 0) {
		//	SDL_Delay(time_to_wait);
		//}
	}
	return Currentstate;
}

void Menu::initialize(SDL_Renderer* renderer) {
	//menu_test { nullptr };
	load_texture(menu_test, "textures/menu_header.png", renderer);
}

void Menu::load_texture(SDL_Texture* & texture_to_load,
		std::string path, SDL_Renderer* renderer) {
	SDL_Surface* temp = IMG_Load(path.c_str());
	texture_to_load = SDL_CreateTextureFromSurface(renderer, temp);

	SDL_FreeSurface(temp);

}

void Menu::handle_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			Currentstate = Gamestate::Playstate;
			break;
		case SDL_MOUSEMOTION:
			//player->setCircleCenter(event.motion.x, event.motion.y);
			break;
		case SDL_QUIT:
			Currentstate = Gamestate::Exit;
			break;
		}
	}
}

void Menu::updateAll() {

}

void Menu::drawAll(SDL_Renderer* renderer) {

	SDL_RenderClear(renderer);
	SDL_Rect r_test { 100, 100, 100, 100 };
	SDL_RenderCopy(renderer, menu_test, nullptr, &r_test);
	SDL_RenderPresent(renderer);
}
