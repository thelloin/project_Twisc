/*
 * Play_Screen.cpp
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "Play_Screen.h"

Play_Screen::Play_Screen() {
	// TODO Auto-generated constructor stub

}

Play_Screen::~Play_Screen() {
	// TODO Auto-generated destructor stub
}

Abstract_Gamestate::Gamestate Play_Screen::run_screen(SDL_Renderer* renderer) {
	Currentstate = Gamestate::Playstate;
	Play_Screen::initialize(renderer);
	while (Currentstate == Gamestate::Playstate) {
		// T
		Uint32 ticksAtLoopStart = SDL_GetTicks();

		Play_Screen::handle_input();
		//GameScreen::updateAll();
		Play_Screen::drawAll(renderer);

		// T
		//int time_to_wait = ticksPerFrame
		//                            - (SDL_GetTicks() - ticksAtLoopStart);
		//if (time_to_wait > 0) {
		//	SDL_Delay(time_to_wait);
		//}
	}
	return Currentstate;
}

void Play_Screen::initialize(SDL_Renderer* renderer) {
	//menu_test { nullptr };
	level = new Level(renderer);
	level->initialize_level(1);
}


void Play_Screen::handle_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEBUTTONDOWN:
			Currentstate = Gamestate::Exit;
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

void Play_Screen::updateAll() {

}

void Play_Screen::drawAll(SDL_Renderer* renderer) {
	level->draw_level(renderer);

}
