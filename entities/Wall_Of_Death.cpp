/*
 * Wall_Of_Death.cpp
 *
 *  Created on: 3 dec 2014
 *      Author: tomli962
 */

#include "Wall_Of_Death.h"



Wall_Of_Death::~Wall_Of_Death() {}

/// Updates the wall movement.
void Wall_Of_Death::update_movement()
{
	obj_rect.x += wall_speed;
}

/// Updates the wall animation
void Wall_Of_Death::update_animation()
{
	if ( animation_counter == ANIMATION_FPS )
	{
		if ( frame_rect.x == 100 )
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

/// Draws the walls texture
void Wall_Of_Death::draw_texture( SDL_Renderer& renderer, double camera_speed, int camera_y_pos )
{
	obj_rect.x -= camera_speed;

	update_animation();
	SDL_RenderCopy( &renderer, &texture, &frame_rect, &obj_rect );
}

/// Sets a new wallspeed, this is done when there is a speedup to the camera speed.
void Wall_Of_Death::set_wall_speed( int new_speed )
{
	wall_speed = new_speed;
}
