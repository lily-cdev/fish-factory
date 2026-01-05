#pragma once
#include <miniaudio.h>
#include <stdbool.h>

typedef struct {
	ma_engine Audio_Engine;
	ma_engine_config Configuration;
	ma_sound Primary_Ambience;
	ma_sound Filtration_Loop;
	ma_sound Ram_Loop;
	ma_sound Click;
} AUDIO;

extern AUDIO Audio;

void Startup_Miniaudio();
void Shutdown_Miniaudio();
void Load_Sound(const char* Path, ma_sound* Target);
void Play_Sound(ma_sound* Target, bool Looping);
void Terminate_Sound(ma_sound* Target);
void Adjust_Sound(float Volume);
void Free_Sound(ma_sound* Target);