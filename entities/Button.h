/*
 * Button.h
 *
 *  Created on: 8 dec 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_BUTTON_H_
#define ENTITIES_BUTTON_H_

#include <SDL2/SDL.h>

#include "Sprite.h"

class Button : public Sprite {
public:
	Button(int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture) :
			Sprite(width, height, x_pos, y_pos,in_texture) {}
	virtual ~Button();
};

#endif /* ENTITIES_BUTTON_H_ */
