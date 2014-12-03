/*
 * Lava.h
 *
 *  Created on: 3 dec 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_LAVA_H_
#define ENTITIES_LAVA_H_

#include "Enemy.h"

class Lava : public Enemy{
public:
	Lava(int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture) :
						Enemy(width, height, x_pos, y_pos,in_texture){}
	virtual ~Lava();

	void update_movement();

};

#endif /* ENTITIES_LAVA_H_ */
