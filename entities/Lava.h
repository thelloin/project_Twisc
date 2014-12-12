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
	Lava( int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture ) :
						Enemy( width, height, x_pos, y_pos,in_texture ), ANIMATION_FPS{30},
						animation_counter{0}, frame_rect{0,0,16,16} {}
	virtual ~Lava();

	void update_movement();
	void draw_texture( SDL_Renderer& renderer, double camera_speed, int camera_y_pos );

private:
	const int ANIMATION_FPS;
	int animation_counter;
	SDL_Rect frame_rect;

	void update_animation();
};

#endif /* ENTITIES_LAVA_H_ */
