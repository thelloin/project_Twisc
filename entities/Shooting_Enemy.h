/*
 * Shooting_Enemy.h
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#ifndef SHOOTING_ENEMY_H_
#define SHOOTING_ENEMY_H_

#include "Enemy.h"

class Shooting_Enemy : public Enemy {
public:
	Shooting_Enemy(int width, int height, int x_pos, int y_pos, SDL_Texture* in_texture) :
					Enemy(width, height, x_pos, y_pos,in_texture), SHOOT_COOLDOWN(50), cooldown_timer(0) {}
	virtual ~Shooting_Enemy();

	void update_movement();
private:
	const int SHOOT_COOLDOWN;
	int cooldown_timer;
};

#endif /* SHOOTING_ENEMY_H_ */
