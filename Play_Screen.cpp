/*
 * Play_Screen.cpp
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */

#include "Play_Screen.h"

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

		if (level_to_load < MAX_LEVEL)
		{
			Play_Screen::drawAll(renderer);
		}

		int time_to_wait = ticksPerFrame - (SDL_GetTicks() - ticksAtLoopStart);
		if (time_to_wait > 0)
		{
			SDL_Delay(time_to_wait);
		}
	}
	return Currentstate;
}

void Play_Screen::initialize(SDL_Renderer& renderer) {
	level = new Level(renderer, level_to_load, Currentstate);
	level->initialize_level();
}


void Play_Screen::handle_input() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );

		switch (event.type)
		{
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
			case SDLK_ESCAPE:
				level->game_menu();
				break;
			case SDLK_p:
				level->pause_game();
				break;
			case SDLK_UP:
				level->change_selection(-1);
				break;
			case SDLK_DOWN:
				level->change_selection(1);
				break;
			case SDLK_RETURN:
				level->execute_selection();
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
		Audio::play_effect("death");
		SDL_Rect temp_rect = {320 - 150,180,300,100};
		level->display_message("die_message", temp_rect);
		SDL_Delay(2000);
		restart_level();
	}
	if (level->get_level_cleared())
	{
		Audio::play_effect("level_cleared");
		SDL_Rect temp_rect = {320 - 150,180,300,100};
		level->display_message("level_cleared_message", temp_rect);
		SDL_Delay(2000);
		next_level();
	}
}

void Play_Screen::drawAll(SDL_Renderer& renderer) {
	level->draw_level(renderer);
}

void Play_Screen::restart_level()
{
	delete level;
	initialize(renderer);
}

void Play_Screen::next_level()
{
	delete level;
	++level_to_load;
	initialize(renderer);
}


