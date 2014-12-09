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

void Wall_Of_Death::update_animation()
{
	if (animation_counter == animation_fps)
	{
		if (frame_rect.x == 100)
		{
			frame_rect.x = 0;
		}
		else
		{
			frame_rect.x = 100;
		}
		animation_counter = 0;
	}
	++animation_counter;
}


void Wall_Of_Death::draw_texture(SDL_Renderer& renderer, double camera_speed, int camera_y_pos)
{
	obj_rect.x -= camera_speed;

	update_animation();
	SDL_RenderCopy(&renderer, &texture, &frame_rect, &obj_rect);
}
