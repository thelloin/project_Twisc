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

	//If the character does not collide on move, move character.
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

	update_y_movement(grounds);

}

bool Player::check_x_collision(std::vector<Ground*> const& grounds, int pos_change)
{
	//Checks for collisions on the horizontal axis.

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
			&& (new_pos.h + new_pos.y)
			< (ground->get_rect().y + ground->get_rect().h);
}

 void Player::update_y_movement(std::vector<Ground*> const& grounds)
 {
	 //Updates the characters vertical speed(y_speed).

	 bool has_collided_bottom{false};

	 SDL_Rect new_pos = obj_rect;

	 //If the character is grounded, he should always check for a
	 //collision below just in case the character would move off a ledge.
	 if (grounded)
	 {
		 new_pos.y += 1;
	 }
	 else
	 {
		 new_pos.y += y_speed;
	 }

	 //Checks for collision both above the character if he hits the ceiling and
	 //below the character if he lands on any ground. If he collides into the ceiling we sets the y_speed to 0
	 //If y_speed is high, the character will check for a collision far away and if so,
	 //we places the character on the ground were it should collide
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
			 y_speed = 0;
			 obj_rect.y = ground->get_rect().y - obj_rect.h;
			 break;
		 }
	 }

	 //If we did not collide we should fall.
	 if (!has_collided_bottom)
	 {
		 obj_rect.y += y_speed;
		 y_speed += GRAVITY;
		 grounded = false;
	 }
 }

void Player::jump()
{
	if (grounded == true)
	{
		grounded = false;
		y_speed = DEFAULT_Y_SPEED;
	}
}


