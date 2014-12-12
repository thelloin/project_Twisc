/*
 * AbstractGamestate.h
 *
 *  Created on: 21 nov 2014
 *      Author: eried975
 */

#ifndef ABSTRACT_GAMESTATE_H_
#define ABSTRACT_GAMESTATE_H_

#include <SDL2/SDL.h>

class Abstract_Gamestate {
public:
	Abstract_Gamestate(){};
	virtual ~Abstract_Gamestate(){};

	enum Gamestate{Menu, Playstate, Gameover, Exit, None};

	virtual Gamestate run_screen(SDL_Renderer& renderer) = 0;

	Gamestate get_state() const { return Currentstate; }

protected:
	virtual void initialize(SDL_Renderer& renderer) = 0;
	virtual void handle_input() = 0;
	virtual void updateAll() = 0;
	virtual void drawAll(SDL_Renderer& renderer) = 0;

	Gamestate Currentstate{Gamestate::None};
};

#endif /* ABSTRACT_GAMESTATE_H_ */
