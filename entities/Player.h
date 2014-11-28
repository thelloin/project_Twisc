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

class Player : public Sprite
{
public:
	Player(int width, int height, int x_pos, int y_pos, SDL_Texture* in_texture) :
			Sprite(width, height, x_pos, y_pos,in_texture),
			GRAVITY{0.2}, DEFAULT_Y_SPEED(-6), y_speed(-6), grounded(true),
			x_speed(3), current_direction(NONE) {}
	virtual ~Player();



	enum Direction{LEFT, RIGHT, NONE};
	void set_direction(Direction dir);
	void update_movement(std::vector<Ground*> const& grounds);
	bool check_x_collision(std::vector<Ground*> const& grounds, int pos_change);

	bool check_y_top_collision(Ground* const& ground, SDL_Rect new_pos);
	bool check_y_bottom_collision(Ground* const& ground, SDL_Rect new_pos);
	void update_y_movement(std::vector<Ground*> const& grounds);
	//bool is_grounded();*/
	void set_grounded(bool grounded);

private:
	const double GRAVITY;
	const int DEFAULT_Y_SPEED;
	bool grounded;
	double y_speed;

	int x_speed;



	Direction current_direction;

};

#endif /* ENTITIES_PLAYER_H_ */
