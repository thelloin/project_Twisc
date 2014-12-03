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
#include "entities/Player.h"



Play_Screen::~Play_Screen()
{

	delete level;
}

Abstract_Gamestate::Gamestate Play_Screen::run_screen(SDL_Renderer& renderer)
{
	Currentstate = Gamestate::Playstate;
	Play_Screen::initialize(renderer);

	const int ticksPerFrame = 1000 / 60;

	while (Currentstate == Gamestate::Playstate) {

		Uint32 ticksAtLoopStart = SDL_GetTicks();

		Play_Screen::handle_input();
		Play_Screen::updateAll();
		Play_Screen::drawAll(renderer);


		int time_to_wait = ticksPerFrame - (SDL_GetTicks() - ticksAtLoopStart);
		if (time_to_wait > 0)
		{
			SDL_Delay(time_to_wait);
		}
	}
	return Currentstate;
}

void Play_Screen::initialize(SDL_Renderer& renderer) {
	//menu_test { nullptr };
	//this->renderer = renderer;
	level = new Level(renderer);
	level->initialize_level(level_to_load);
}


void Play_Screen::handle_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

		switch (event.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			Currentstate = Gamestate::Exit;
			break;
		case SDL_MOUSEMOTION:
			//player->setCircleCenter(event.motion.x, event.motion.y);
			break;
		case SDL_QUIT:
			Currentstate = Gamestate::Exit;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				(level->get_player())->set_direction(Player::LEFT);
				break;
			case SDLK_d:
				(level->get_player())->set_direction(Player::RIGHT);
				break;
			case SDLK_w:
				(level->get_player())->jump();
				break;
			case SDLK_SPACE:
				(level->get_player())->dash();
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_a:
				if (!currentKeyStates[ SDL_SCANCODE_D])
				{
					(level->get_player())->set_direction(Player::NONE);
				}
				break;
			case SDLK_d:
				if (!currentKeyStates[ SDL_SCANCODE_A])
				{
				(level->get_player())->set_direction(Player::NONE);
				}
				break;
			}
		}
	}
}

void Play_Screen::updateAll()
{
	level->update_level();

	// Check if the player has died
	if (level->get_player()->get_dead_status())
	{
		restart_level();
	}
}

void Play_Screen::drawAll(SDL_Renderer& renderer) {
	level->draw_level(renderer);
}

void Play_Screen::restart_level()
{
	delete level;
	level_to_load = 2;
	initialize(renderer);
}
