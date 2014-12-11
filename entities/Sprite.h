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
	virtual ~Sprite();

	SDL_Rect& get_rect() {return obj_rect;}

	virtual void draw_texture(SDL_Renderer& renderer, double camera_speed, int camera_y_pos);

protected:
	Sprite(int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture);

	SDL_Rect obj_rect;
	SDL_Texture& texture;
};

#endif /* ENTITIES_SPRITE_H_ */
