/*
 * Shooting_Enemy.cpp
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#include <vector>
#include <iostream>

#include "Shooting_Enemy.h"
#include "Bullet.h"

Shooting_Enemy::~Shooting_Enemy() {
	// TODO Auto-generated destructor stub
}

void Shooting_Enemy::update_movement()
{
	shoot();
}

void Shooting_Enemy::shoot()
{
	if (cooldown_timer >= SHOOT_COOLDOWN)
	{
		enemies.push_back(new Bullet(10, 10, obj_rect.x, (obj_rect.y + obj_rect.w/2), bullet_texture));
		cooldown_timer = 0;
	}
	++cooldown_timer;
}
