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
			Sprite(width, height, x_pos, y_pos,in_texture), y_speed(1), x_speed(3), current_direction(NONE) {}
	virtual ~Player();



	enum Direction{LEFT, RIGHT, NONE};
	void set_direction(Direction dir);
	void update_movement(std::vector<Ground*> const& grounds);
	bool check_x_collision(std::vector<Ground*> const& grounds, int pos_change);
	//bool is_colliding(SDL_Rect new_pos);
	/*bool check_y_collision();
	bool is_grounded();*/

private:
	double y_speed;
	int x_speed;

	Direction current_direction;

};

#endif /* ENTITIES_PLAYER_H_ */
