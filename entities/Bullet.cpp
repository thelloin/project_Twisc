/*
 * Bullet.cpp
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#include "Bullet.h"

Bullet::~Bullet() {}

void Bullet::update_movement()
{
	obj_rect.x += BULLET_SPEED;
	++life_counter;
	if (life_counter >= lifetime)
	{
		destroyed = true;
	}

}

