/*
 * Bullet.h
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_BULLET_H_
#define ENTITIES_BULLET_H_

#include "Enemy.h"

class Bullet : public Enemy
{
public:
	Bullet(int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture) :
						Enemy(width, height, x_pos, y_pos,in_texture), BULLET_SPEED(-2), LIFETIME(240),
						life_counter(0), destroyed(false) {}
	virtual ~Bullet();

	void update_movement();

	bool is_destroyed() const { return destroyed; }

private:
	const int BULLET_SPEED;

	const int LIFETIME;
	int life_counter;
	bool destroyed;
};

#endif /* ENTITIES_BULLET_H_ */
