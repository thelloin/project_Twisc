/*
 * Wall_Of_Death.h
 *
 *  Created on: 3 dec 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_WALL_OF_DEATH_H_
#define ENTITIES_WALL_OF_DEATH_H_

#include "Enemy.h"


class Wall_Of_Death : public Enemy{
public:
	Wall_Of_Death(int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture, int speed) :
						Enemy(width, height, x_pos, y_pos,in_texture), WALL_SPEED(speed) {}
	virtual ~Wall_Of_Death();

	void update_movement();

private:
	const int WALL_SPEED;
};

#endif /* ENTITIES_WALL_OF_DEATH_H_ */
