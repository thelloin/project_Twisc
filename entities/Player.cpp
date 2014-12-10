/*
 * Player.cpp
 *
 *  Created on: 28 nov 2014
 *      Author: eried975
 */
#include "Player.h"

Player::~Player() {}

void Player::set_direction(Direction dir)
{
	current_direction = dir;
}

void Player::update_movement(std::vector<Ground*> const& grounds) {

	//If the character does not collide on move, move character.
	switch (current_direction) {
	case (LEFT):
		if (!check_x_collision(grounds, -x_speed))
		{
			facing_direction = LEFT;
			obj_rect.x -= x_speed;
		}
		break;
	case (RIGHT):
		if (!check_x_collision(grounds, x_speed) && obj_rect.x < 590)
		{
			facing_direction = RIGHT;
			obj_rect.x += x_speed;
		}
		break;
	default:
		break;
	}

	// Updates the dash time counter if the player is dashing and
	// stops dashing when dash timer reaches the const DASH_TIME
	if (is_dashing)
	{
		++dash_timer;
		if (dash_timer >= DASH_TIME)
		{
			is_dashing = false;
			dash_timer = 0;
			if (has_powerup == false)
			{
				x_speed = DEFAULT_X_SPEED;
			}
		}

	}

	if (has_powerup == true)
	{
		++power_timer;

		// We dont want to change the speed if we are dashing.
		if (is_dashing == false)
		{
			x_speed = (DEFAULT_X_SPEED + POWER_SPEED);
		}

		if (power_timer > POWER_TIME)
		{
			has_powerup = false;
			power_timer = 0;

			if (is_dashing == false)
			{
				x_speed = DEFAULT_X_SPEED;
			}
		}
	}

	update_y_movement(grounds);

}

void Player::handle_collisions(std::vector<Enemy*>& enemies, Button* const& button)
{
	// Check if there is a collision with the character and all enemies and bullets
	for (unsigned int i{0}; i < enemies.size(); ++i)
	{
		// Try to cast the enemy to a Shooting_Enemy
		Shooting_Enemy* shooting_enemy = dynamic_cast<Shooting_Enemy*>(enemies[i]);
		Bullet* bullet = dynamic_cast<Bullet*>(enemies[i]);
		if (shooting_enemy != nullptr)
		{
			if (intersect(shooting_enemy, 0) && !is_dashing)
			{
				is_dead = true;
			}
			else if (intersect(shooting_enemy,0) && is_dashing)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				has_powerup = true;
			}
		}
		else if (bullet != nullptr)
		{
			if (intersect(bullet, 0) && !is_dashing)
			{
				is_dead = true;
			}
			else if (intersect(bullet,0) && is_dashing)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}
		// The enemy object is a bullet or the wall of death
		else
		{
			if (intersect(enemies[i], 0))
			{
				is_dead = true;
			}
		}

	}


}

bool Player::intersect(Sprite* const& sprite, int pos_change) const
{
	SDL_Rect new_pos = obj_rect;
	new_pos.x += pos_change;

	bool x_inter = (new_pos.x < (sprite->get_rect().w + sprite->get_rect().x)
			                  && (new_pos.w + new_pos.x) > sprite->get_rect().x);
	bool y_inter = (new_pos.y < (sprite->get_rect().h + sprite->get_rect().y)
			                  && (new_pos.h + new_pos.y) > sprite->get_rect().y);

	return x_inter && y_inter;
}

bool Player::check_x_collision(std::vector<Ground*> const& grounds, int pos_change)
{
	//Checks for collisions with Grounds on the horizontal axis when moving.

	bool has_collided{false};

	for (Ground* ground: grounds)
	{
		if ( intersect(ground, pos_change) )
		{
			has_collided = true;
			break;
		}
	}

	// Check if we have collided with an object and if the character is dashing
	if (has_collided && is_dashing)
	{
		is_dead = true;
	}
	return has_collided;
}

bool Player::check_y_top_collision(Ground* const& ground, SDL_Rect new_pos) const
{
	return (new_pos.y < (ground->get_rect().h + ground->get_rect().y))
			&& (new_pos.y > ground->get_rect().y);
}

bool Player::check_y_bottom_collision(Ground* const& ground, SDL_Rect new_pos) const
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
			 can_dash = true;
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
		Audio::play_effect("jump");

	}
}

// Sets the dash-mode to true and changes the x_speed
void Player::dash()
{
	if (can_dash && !is_dashing && current_direction != NONE)
	{
		x_speed = DASH_SPEED;
		is_dashing = true;
		Audio::play_effect("dash");
		if (!grounded)
		{
			can_dash = false;
		}

	}
}

bool Player::button_pushed(Button* const& button) const
{
	return intersect(button, 0);
}

void Player::draw_texture(SDL_Renderer& renderer, double camera_speed, int camera_y_pos)
{
	obj_rect.y = (obj_rect.y - camera_y_pos);
	obj_rect.x -= camera_speed;
	update_animation();

	if (facing_direction == RIGHT)
	{
		SDL_RenderCopy(&renderer, &texture, &frame_rect, &obj_rect);
	}
	if (facing_direction == LEFT)
	{
		SDL_RenderCopyEx(&renderer, &texture, &frame_rect, &obj_rect, 0, nullptr, SDL_FLIP_HORIZONTAL);
	}
}

void Player::update_animation()
{
	//Walking animation
	if ((current_direction == RIGHT || current_direction == LEFT) && grounded == true)
	{
		frame_rect.y = 0;
		if (animation_counter == ANIMATION_FPS)
		{
			if (frame_rect.x < 54)
			{
				frame_rect.x += FRAME_LENGTH;
			}
			else
			{
				frame_rect.x = 0;
			}
			animation_counter = 0;
		}
		++animation_counter;
	}
	//If we are jumping but not dashing
	else if (grounded == false && is_dashing == false)
	{
		frame_rect.x = 0;
		frame_rect.y = FRAME_HEIGHT;
	}
	//If we are standing still
	else
	{
		frame_rect.x = 0;
		frame_rect.y = 0;
	}
	//If we are dashing
	if (is_dashing == true)
	{
		frame_rect.x = FRAME_LENGTH;
		frame_rect.y = FRAME_HEIGHT;
	}
}


