/*
 * Lava.cpp
 *
 *  Created on: 3 dec 2014
 *      Author: tomli962
 */

#include "Lava.h"


Lava::~Lava() {
	// TODO Auto-generated destructor stub
}

void Lava::update_movement()
{

}


void Lava::update_animation()
{
	if (animation_counter == animation_fps)
	{
		if (frame_rect.x == 16)
		{
			frame_rect.x = 0;
		}
		else
		{
			frame_rect.x = 16;
		}
		animation_counter = 0;
	}
	++animation_counter;
}


void Lava::draw_texture(SDL_Renderer& renderer, double camera_speed, int camera_y_pos)
{
	obj_rect.y = (obj_rect.y - camera_y_pos);
	obj_rect.x -= camera_speed;

	update_animation();
	SDL_RenderCopy(&renderer, &texture, &frame_rect, &obj_rect);
}
