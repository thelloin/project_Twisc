/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: eried975
 */

#include "Player.h"
#include <iostream>
void Player::set_direction(Direction dir)
{
	current_direction = dir;
}
Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::update_movement(std::vector<Ground*> const& grounds) {

	switch (current_direction) {
	case (LEFT):
		std::cout << "Left" << std::endl;
		if (!check_x_collision(grounds, -x_speed))
		{
			obj_rect.x -= x_speed;
		}
		break;
	case (RIGHT):
		if (!check_x_collision(grounds, x_speed))
		{
			obj_rect.x += x_speed;
		}
		break;
	default:
		break;
	}
	obj_rect.y += y_speed;
}

bool Player::check_x_collision(std::vector<Ground*> const& grounds, int pos_change)
{
	bool has_collided{false};
	for (Ground* ground: grounds)
	{
		SDL_Rect new_pos = obj_rect;
		new_pos.x += pos_change;

		bool x_inter = (new_pos.x < (ground->get_rect().w + ground->get_rect().x)
		                  && (new_pos.w + new_pos.x) > ground->get_rect().x);
		bool y_inter = (new_pos.y < (ground->get_rect().h + ground->get_rect().y)
		                  && (new_pos.h + new_pos.y) > ground->get_rect().y);
		if (x_inter && y_inter)
		{
			has_collided = true;
			break;
		}
	}
	return has_collided;
}
/* bool check_y_collision();
 bool is_grounded();*/
