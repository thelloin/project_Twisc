/*
 * Shooting_Enemy.h
 *
 *  Created on: 2 dec 2014
 *      Author: tomli962
 */

#ifndef SHOOTING_ENEMY_H_
#define SHOOTING_ENEMY_H_

#include <vector>
#include <SDL2/SDL.h>

#include "Enemy.h"
#include "Bullet.h"
#include "../Audio.h"

class Shooting_Enemy : public Enemy {
public:
	Shooting_Enemy(int width, int height, int x_pos, int y_pos,
			SDL_Texture& in_texture, std::vector<Enemy*> & enemies, SDL_Texture& bullet_texture) :
					Enemy(width, height, x_pos, y_pos,in_texture),
					SHOOT_COOLDOWN(180), cooldown_timer(SHOOT_COOLDOWN), enemies(enemies), bullet_texture(bullet_texture) {}
	virtual ~Shooting_Enemy();

	void update_movement();



private:
	const int SHOOT_COOLDOWN;
	int cooldown_timer;
	std::vector<Enemy*>& enemies;
	SDL_Texture& bullet_texture;

	int counter{0};


	void shoot();
};

#endif /* SHOOTING_ENEMY_H_ */
