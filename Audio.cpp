/*
 * Audio.cpp
 *
 *  Created on: 10 dec 2014
 *      Author: tomli962
 */
#include "Audio.h"

std::map<std::string ,Mix_Chunk*> Audio::audio_track;
Mix_Music* Audio::music;


Audio::Audio() {

}

Audio::~Audio() {}


void Audio::initialize()
{
	// Load the sound effects
	Mix_Chunk* temp_effect = Mix_LoadWAV( "audio/shoot.wav" );
	audio_track["shoot"] = temp_effect;

	temp_effect = Mix_LoadWAV( "audio/jump.wav" );
	audio_track["jump"] = temp_effect;

	temp_effect = Mix_LoadWAV( "audio/dash.wav" );
	audio_track["dash"] = temp_effect;

	temp_effect = Mix_LoadWAV( "audio/death.wav" );
	audio_track["death"] = temp_effect;

	temp_effect = Mix_LoadWAV( "audio/level_cleared.wav" );
	audio_track["level_cleared"] = temp_effect;

	// Load and start the background music
	music = Mix_LoadMUS( "audio/background_music.mp3" );
	Mix_PlayMusic(music, -1);

}


void Audio::play_effect(std::string effect_name)
{
	Mix_PlayChannel( -1, audio_track[effect_name], 0 );
}

void Audio::destroy_sound()
{
	//Free the sound effects
	Mix_FreeChunk( audio_track["shoot"] );
	Mix_FreeChunk( audio_track["jump"] );
	Mix_FreeChunk( audio_track["dash"] );
	Mix_FreeChunk( audio_track["death"] );
	Mix_FreeChunk( audio_track["level_cleared"] );
	Mix_FreeMusic(music);
}
