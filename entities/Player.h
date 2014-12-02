/*
 * Player.h
 *
 *  Created on: 28 nov 2014
 *      Author: eried975
 */

#ifndef ENTITIES_PLAYER_H_
#define ENTITIES_PLAYER_H_

#include <SDL2/SDL.h>
#include <vector>

#include "Sprite.h"
#include "Ground.h"
#include "Enemy.h"

class Player : public Sprite
{
public:
	Player(int width, int height, int x_pos, int y_pos, SDL_Texture* in_texture) :
			Sprite(width, height, x_pos, y_pos,in_texture),
			GRAVITY{0.2}, DEFAULT_Y_SPEED(-6), DEFAULT_X_SPEED(3), grounded(true), is_dashing(false),
			DASH_TIME(5), dash_timer(0), DASH_SPEED(20 ), y_speed(0),
			x_speed(DEFAULT_X_SPEED), current_direction(NONE) {}
	virtual ~Player();



	enum Direction{LEFT, RIGHT, NONE};
	void set_direction(Direction dir);

	void jump();
	void dash();

	void update_movement(std::vector<Ground*> const& grounds);

	bool intersect(Sprite* const& sprite, int pos_change) const;
	void handle_collisions(std::vector<Enemy*>& enemies);
	bool check_x_collision(std::vector<Ground*> const& grounds, int pos_change);

	bool check_y_top_collision(Ground* const& ground, SDL_Rect new_pos);
	bool check_y_bottom_collision(Ground* const& ground, SDL_Rect new_pos);
	void update_y_movement(std::vector<Ground*> const& grounds);

	bool get_dead_status() { return is_dead; }

private:
	const double GRAVITY;
	const int DEFAULT_Y_SPEED;
	const int DEFAULT_X_SPEED;

	bool grounded;

	bool is_dashing;
	const int DASH_TIME;
	int dash_timer;
	const int DASH_SPEED;

	double y_speed;
	int x_speed;

	bool is_dead{false};
	Direction current_direction;

};

#endif /* ENTITIES_PLAYER_H_ */
