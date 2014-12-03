/*
 * Sprite.cpp
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */

#include "Sprite.h"
#include "Player.h"

Sprite::Sprite(int width, int height, int x_pos, int y_pos, SDL_Texture& in_texture) : texture(in_texture)
	{
		obj_rect.w = width;
		obj_rect.h = height;
		obj_rect.x = x_pos;
		obj_rect.y = y_pos;
	}

Sprite::~Sprite() {
	// The texture is removed in level with SDL_DestroyTexture()
	//texture = nullptr;
}

void Sprite::draw_texture(SDL_Renderer* renderer, double camera_speed, int camera_y_pos)
{
	obj_rect.y = (obj_rect.y - camera_y_pos);
	obj_rect.x -= camera_speed;

	SDL_RenderCopy(renderer, &texture, nullptr, &obj_rect);
}
