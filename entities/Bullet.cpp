/*
 * Bullet.cpp
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */
#include <iostream>

#include "Bullet.h"

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::update_movement()
{
	std::cout << get_rect().w << std::endl;
	obj_rect.x += BULLET_SPEED;

}

