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

	/*if (grounded)
	{
	for (Ground* g: grounds)
		{
			SDL_Rect new_rect = obj_rect;
			new_rect.y += y_speed;
			if (check_y_bottom_collision(g,new_rect ))
			{
				grounded = false;
			}
		}
	}*/

	if (!grounded)
	{
		/*obj_rect.y += y_speed;
		y_speed += gravity;
		std::cout << y_speed << std::endl;
		if (y_speed > 6 )
		{
			grounded = true;
			y_speed = -6;
		}*/
		update_y_movement(grounds);

	}
}

bool Player::check_x_collision(std::vector<Ground*> const& grounds, int pos_change)
{
	bool has_collided{false};

	SDL_Rect new_pos = obj_rect;
	new_pos.x += pos_change;

	for (Ground* ground: grounds)
	{
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

bool Player::check_y_top_collision(Ground* const& ground, SDL_Rect new_pos)
{
	return (new_pos.y < (ground->get_rect().h + ground->get_rect().y))
			&& (new_pos.y > ground->get_rect().y);
}

bool Player::check_y_bottom_collision(Ground* const& ground, SDL_Rect new_pos)
{
	return (new_pos.h + new_pos.y) > ground->get_rect().y
			&& (new_pos.h + new_pos.y) < (ground->get_rect().y + ground->get_rect().h);
}

 void Player::update_y_movement(std::vector<Ground*> const& grounds)
 {
	 bool has_collided_bottom{false};

	 SDL_Rect new_pos = obj_rect;
	 new_pos.y += y_speed;

	 for (Ground* ground: grounds)
	 {
		 bool x_inter = (new_pos.x < (ground->get_rect().w + ground->get_rect().x)
                         && (new_pos.w + new_pos.x) > ground->get_rect().x);

		 bool y_top_inter = check_y_top_collision(ground, new_pos);
		 bool y_bottom_inter = check_y_bottom_collision(ground, new_pos);

		 if (x_inter && y_top_inter)
		 {
			 y_speed = 0;
		 }
		 if (x_inter && y_bottom_inter)
		 {
			 has_collided_bottom = true;
			 grounded = true;
			 y_speed = -6;
			 break;
		 }
	 }
	 std::cout << has_collided_bottom << std::endl;
	 if (!has_collided_bottom)
	 {
		 obj_rect.y += y_speed;
		 y_speed += GRAVITY;
	 }


	 std::cout << "hej" << std::endl;
 }
 //bool is_grounded();

void Player::set_grounded(bool grounded)
{
	this->grounded = grounded;
}
