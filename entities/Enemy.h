/*
 * Enemy.h
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_ENEMY_H_
#define ENTITIES_ENEMY_H_

#include "Sprite.h"

class Enemy : public Sprite
{
public:
	Enemy( int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture ) :
				Sprite( width, height, x_pos, y_pos,in_texture ) {}
	virtual ~Enemy();

	virtual void update_movement() = 0;

	bool is_within_screen( SDL_Rect& camera_position ) const;
};

#endif /* ENTITIES_ENEMY_H_ */
