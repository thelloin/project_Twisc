/*
 * Wall_Of_Death.cpp
 *
 *  Created on: 3 dec 2014
 *      Author: tomli962
 */

#include "Wall_Of_Death.h"



Wall_Of_Death::~Wall_Of_Death() {
	// TODO Auto-generated destructor stub
}

void Wall_Of_Death::update_movement()
{
	obj_rect.x += WALL_SPEED;
}

