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
#include <SDL2/SDL_mixer.h>

#include "Abstract_Gamestate.h"
#include "Menu.h"
#include "Play_Screen.h"

using namespace std;

// Load the music
void load_music(Mix_Music*&);

int main(int argc, char* argv[]) {
	//srand(time(nullptr));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "Unable to initialize SDL: " << SDL_GetError()
				<< std::endl;
		return 1;
	}

	 if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
	 {
		 printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	 }
	atexit(SDL_Quit);

	// create the window
	SDL_Window* window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	// make the scaled rendering look smoother
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	// render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, 640, 480);

	Mix_Music* music = NULL;
	load_music(music);

	Abstract_Gamestate* game = new Menu();
	while (game->get_state() != game->Gamestate::Exit)
	{
		game->run_screen(*renderer);
		switch (game->get_state())
		{
		case game->Gamestate::Exit:
			std::cout << "You exited the game!" << std::endl;
			delete game;
			return 0;
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
			break;
		}
	}

	//delete game;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	game = nullptr;
	renderer = nullptr;
	window = nullptr;
	SDL_Quit();
	/////
	return 0;

}

void load_music(Mix_Music*& music)
{
	music = Mix_LoadMUS( "audio/background_music.mp3" );
	Mix_PlayMusic(music, -1);
}

