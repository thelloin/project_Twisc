/*
 * game.cpp
 *
 *  Created on: 18 nov 2014
 *      Author: eried975
 */
#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>

#include "Abstract_Gamestate.h"
#include "Menu.h"
#include "Play_Screen.h"

using namespace std;

int main(int argc, char* argv[]) {
	//srand(time(nullptr));

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError()
				<< std::endl;
		return 1;
	}

	atexit(SDL_Quit);

	// create the window
	SDL_Window* window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 1280, 960, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// make the scaled rendering look smoother
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	// render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, 1280, 960);

	Abstract_Gamestate* game = new Menu();
	while (game->get_state() != game->Gamestate::Exit)
	{
		game->run_screen(renderer);
		switch (game->get_state())
		{
		case game->Gamestate::Exit:
			std::cout << "You exited the game!" << std::endl;
			delete game;
			return 0;
			break;
		case game->Gamestate::Menu:
			game = new Menu();
			break;
		case game->Gamestate::Playstate:
			game = new Play_Screen();
			break;
		default:
			// do nothing
			break;
		}

	}
	/////
	return 0;

}

