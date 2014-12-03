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
						Enemy(width, height, x_pos, y_pos,in_texture), BULLET_SPEED(-2) {}
	virtual ~Bullet();

	void update_movement();

private:
	const int BULLET_SPEED;
};

#endif /* ENTITIES_BULLET_H_ */
