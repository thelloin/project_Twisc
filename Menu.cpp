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



Menu::~Menu() {
	SDL_DestroyTexture(textures["play_button"]);
	SDL_DestroyTexture(textures["title"]);
	SDL_DestroyTexture(textures["quit"]);
}

Abstract_Gamestate::Gamestate Menu::run_screen(SDL_Renderer& renderer) {
	Currentstate = Gamestate::Menu;
	Menu::initialize(renderer);

	const int ticksPerFrame = 1000 / 60;

	while (Currentstate == Gamestate::Menu) {
		// T
		Uint32 ticksAtLoopStart = SDL_GetTicks();

		Menu::handle_input();
		//GameScreen::updateAll();
		Menu::drawAll(renderer);

		// T
		int time_to_wait = ticksPerFrame - (SDL_GetTicks() - ticksAtLoopStart);
		if (time_to_wait > 0)
		{
			SDL_Delay(time_to_wait);
		}
	}
	return Currentstate;
}

void Menu::initialize(SDL_Renderer& renderer)
{
	//menu_test { nullptr };
	//load_texture(menu_test, "textures/menu_header.png", renderer);

	SDL_Surface* temp = IMG_Load("textures/play_button.png");
	textures["play_button"] = SDL_CreateTextureFromSurface(&renderer, temp);
	SDL_Rect temp_rect{275,230,temp->w / 2 + 20,temp->h / 2 + 20};
	rects["play_button_rect"] = temp_rect;
	SDL_FreeSurface(temp);


	temp = IMG_Load("textures/title_menu.png");
	textures["title"] = SDL_CreateTextureFromSurface(&renderer, temp);
	temp_rect = {70, 0, temp->w, temp->h};
	rects["title"] = temp_rect;
	SDL_FreeSurface(temp);

	temp = IMG_Load("textures/quit_button.png");
	textures["quit"] = SDL_CreateTextureFromSurface(&renderer, temp);
	temp_rect = {275, 320, temp->w / 2 - 10, temp->h / 2 - 10};
	rects["quit"] = temp_rect;
	SDL_FreeSurface(temp);


}

void Menu::handle_input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Currentstate = Gamestate::Exit;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				--selected_button;
				change_selection();
				break;
			case SDLK_DOWN:
				++selected_button;
				change_selection();
				break;
			case SDLK_RETURN:
				execute_selection();
				break;
			}
			break;
		}
	}
}

void Menu::updateAll() {

}

void Menu::drawAll(SDL_Renderer& renderer) {

	SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
	SDL_RenderClear(&renderer);

	SDL_RenderCopy(&renderer, textures["title"], nullptr, &rects["title"]);
	SDL_RenderCopy(&renderer, textures["quit"], nullptr, &rects["quit"]);
	SDL_RenderCopy(&renderer, textures["play_button"], nullptr, &rects["play_button_rect"]);


	SDL_RenderPresent(&renderer);
}

void Menu::change_selection()
{
	//Makes the selection "loop"
	if (selected_button > 1)
	{
		selected_button = 0;
	}

	if (selected_button < 0)
	{
		selected_button = 1;
	}
	//Changed the rectangles size if selected
	if (selected_button == 0)
	{
		rects["play_button_rect"].w += 20;
		rects["play_button_rect"].h += 20;
		rects["quit"].w -= 20;
		rects["quit"].h -= 20;
	}

	if (selected_button == 1)
	{
		rects["play_button_rect"].w -= 20;
		rects["play_button_rect"].h -= 20;
		rects["quit"].w += 20;
		rects["quit"].h += 20;
	}
}

void Menu::execute_selection()
{
	if (selected_button == 0)
	{
		Currentstate = Gamestate::Playstate;
	}
	if (selected_button == 1)
	{
		Currentstate = Gamestate::Exit;
	}

}
