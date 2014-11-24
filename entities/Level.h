/*
 * Level.h
 *
 *  Created on: 24 nov 2014
 *      Author: tomli962
 */

#ifndef ENTITIES_LEVEL_H_
#define ENTITIES_LEVEL_H_

#include <vector>

#include "Ground.h"

class Level {
public:
	Level();
	virtual ~Level();

	void initialize_level(int level);
	void update_level();
	void draw_level();
private:
	//Player player;
	//vector<Monsters> monsters;
	//vector<bullets> bullets;
	std::vector<Ground*> grounds;
};

#endif /* ENTITIES_LEVEL_H_ */
