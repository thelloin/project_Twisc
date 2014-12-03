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

class Shooting_Enemy : public Enemy {
public:
	Shooting_Enemy(int width, int height, int x_pos, int y_pos,
			SDL_Texture& in_texture, std::vector<Bullet*> & bullets, SDL_Texture& bullet_texture) :
					Enemy(width, height, x_pos, y_pos,in_texture),
					SHOOT_COOLDOWN(6), cooldown_timer(0), bullets(bullets), bullet_texture(bullet_texture) {}
	virtual ~Shooting_Enemy();

	void update_movement();


	int counter = 0;

private:
	const int SHOOT_COOLDOWN;
	int cooldown_timer;
	std::vector<Bullet*>& bullets;
	SDL_Texture& bullet_texture;


	void shoot();
};

#endif /* SHOOTING_ENEMY_H_ */
