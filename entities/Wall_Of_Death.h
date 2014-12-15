/*
 * Wall_Of_Death.h
 *
 *  Created on: 3 dec 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_WALL_OF_DEATH_H_
#define ENTITIES_WALL_OF_DEATH_H_

#include "Enemy.h"
#include <SDL2/SDL.h>


/// Represents the wall of death, inherits from Enemy
class Wall_Of_Death : public Enemy
{
public:
	Wall_Of_Death( int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture, int speed ) :
						Enemy( width, height, x_pos, y_pos,in_texture ), wall_speed{speed},
						ANIMATION_FPS{4}, animation_counter{0}, frame_rect{0,0,99,200} {}
	virtual ~Wall_Of_Death();

	void update_movement();
	void draw_texture( SDL_Renderer& renderer, double camera_speed, int camera_y_pos );

	void set_wall_speed( int new_speed );

private:
	void update_animation();

	int wall_speed;

	const int ANIMATION_FPS;
	int animation_counter;
	SDL_Rect frame_rect;
};

#endif /* ENTITIES_WALL_OF_DEATH_H_ */
