/*
 * Sprite.cpp
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */

#include "Sprite.h"

Sprite::Sprite(int width, int height, int x_pos, int y_pos, SDL_Texture* in_texture) : width(width), height(height),
	x_pos(x_pos) , y_pos(y_pos) , texture(in_texture) {}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}
