#pragma once
#include <miniaudio.h>
#include <stdbool.h>
#define LDE_AUDIOCOUNT 4

typedef struct {
	bool Allocated;
	float Volume;
    ma_sound Data;
} Subsound;

typedef enum {
	Ambience1,
	Filtration1,
	Ram1,
	Click
} Sound;

typedef struct {
	ma_engine Engine;
	Subsound Data[LDE_AUDIOCOUNT];
} AUDIO;

extern AUDIO Audio;

ma_result Startup_Miniaudio();
void Shutdown_Miniaudio();
ma_result Load_Sounds();
void Play_Sound(Sound Target, bool Looping);
void Terminate_Sound(Sound Target);
void Adjust_Sound(float Volume);
void Free_Sounds();