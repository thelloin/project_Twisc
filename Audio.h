/*
 * Audio.h
 *
 *  Created on: 10 dec 2014
 *      Author: tomli962
 */

#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL2/SDL_mixer.h>

#include <map>

class Audio {
public:
	Audio();
	virtual ~Audio();

	static void play_effect(std::string effect_name);

	static void initialize();
	static void destroy_sound();
private:
	static std::map<std::string ,Mix_Chunk*> audio_track;
	static Mix_Music* music;
};

#endif /* AUDIO_H_ */
