/*
 * Enemy.cpp
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#include "Enemy.h"



Enemy::~Enemy() {
	// TODO Auto-generated destructor stub
}

bool Enemy::is_within_screen(SDL_Rect& camera_position) const
{
	return (obj_rect.x < (camera_position.w + camera_position.x)
            && (obj_rect.w + obj_rect.x) > camera_position.x);
}
