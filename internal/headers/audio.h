#pragma once
#include <miniaudio.h>
#include <stdbool.h>

typedef struct {
    ma_sound Data;
	bool Allocated;
} Sound;

typedef struct {
	ma_engine Audio_Engine;
	ma_engine_config Configuration;
	Sound Primary_Ambience;
	Sound Filtration_Loop;
	Sound Ram_Loop;
	Sound Click;
} AUDIO;

extern AUDIO Audio;

int Startup_Miniaudio();
void Shutdown_Miniaudio();
void Load_Sound(const char* Path, Sound* Target);
void Play_Sound(Sound* Target, bool Looping);
void Terminate_Sound(Sound* Target);
void Adjust_Sound(float Volume);
void Free_Sound(Sound* Target);