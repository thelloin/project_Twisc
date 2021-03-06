/*
 * Ground.h
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_GROUND_H_
#define ENTITIES_GROUND_H_

#include <SDL2/SDL.h>

#include "Sprite.h"


/// Represents a ground object, inherits from sprite
class Ground : public Sprite
{
public:
	Ground( int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture ) :
		Sprite( width, height, x_pos, y_pos,in_texture ) {}

	virtual ~Ground(){};
};

#endif /* ENTITIES_GROUND_H_ */
