/*
 * Shooting_Enemy.cpp
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#include "Shooting_Enemy.h"


Shooting_Enemy::~Shooting_Enemy() {}

/// Updates the Shooting_Enemy. In this case it will only shoot.
void Shooting_Enemy::update_movement()
{
	shoot();
}

/// Makes the enemy shoot
void Shooting_Enemy::shoot()
{
	if ( cooldown_timer >= SHOOT_COOLDOWN )
	{
		enemies.push_back( new Bullet( 10, 10, obj_rect.x, ( obj_rect.y + obj_rect.w/2 ), bullet_texture ) );
		cooldown_timer = 0;
		Audio::play_effect( "shoot" );
	}
	++cooldown_timer;
}
