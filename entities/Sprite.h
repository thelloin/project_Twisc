/*
 * Sprite.h
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_SPRITE_H_
#define ENTITIES_SPRITE_H_

#include <SDL2/SDL.h>

class Sprite {
public:
	Sprite(int width, int height, int x_pos, int y_pos, SDL_Texture* in_texture);
	virtual ~Sprite();

	//virtual SDL_Rect* get_collision_rect() = 0;
	//virtual void draw_texture() = 0;
	//virtual void set_pos(int x_pos, int y_pos);
private:
	const int width;
	const int height;
	int x_pos;
	int y_pos;

	SDL_Texture* texture;
};

#endif /* ENTITIES_SPRITE_H_ */
