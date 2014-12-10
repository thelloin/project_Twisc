/*
 * game.cpp
 *
 *  Created on: 18 nov 2014
 *      Author: eried975
 */
#include <iostream>

#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "Abstract_Gamestate.h"
#include "Menu.h"
#include "Play_Screen.h"
#include "Audio.h"

using namespace std;

// Load the music
void load_music();

void init_game(SDL_Window*& window, SDL_Renderer*& renderer);

void run_game(Abstract_Gamestate* game, SDL_Renderer*& renderer);

void destroy_game(SDL_Window*& window, SDL_Renderer*& renderer, Abstract_Gamestate* game);

int main(int argc, char* argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;

	Abstract_Gamestate* game = new Menu();

	init_game(window, renderer);
	run_game(game, renderer);
	destroy_game(window, renderer, game);

	return 0;

}

void init_game(SDL_Window*& window, SDL_Renderer*& renderer)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError()
				<< std::endl;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	atexit(SDL_Quit);

	// create the window
	window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);

	// make the scaled rendering look smoother
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	// render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, 640, 480);


	load_music();
}

void run_game(Abstract_Gamestate* game, SDL_Renderer*& renderer)
{

	while (game->get_state() != game->Gamestate::Exit)
	{
		game->run_screen(*renderer);
		switch (game->get_state())
		{
		case game->Gamestate::Exit:
			delete game;
			break;
		case game->Gamestate::Menu:
			delete game;
			game = new Menu();
			break;
		case game->Gamestate::Playstate:
			delete game;
			game = new Play_Screen(*renderer);
			break;
		default:
			// do nothing
			delete game;
			break;
		}
	}
}

void destroy_game(SDL_Window*& window, SDL_Renderer*& renderer, Abstract_Gamestate* game)
{
	//delete game;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	game = nullptr;
	renderer = nullptr;
	window = nullptr;
	Audio::destroy_sound();
	SDL_Quit();
}

void load_music()
{
	Audio::initialize();
}

