#pragma once
#include <miniaudio.h>
#include <stdbool.h>
#define LDE_AUDIOCOUNT 4;
#define LDE_FORMAT ma_format_f32
#define LDE_CHANNELS 2
#define LDE_SAMPLERATE 44100

typedef struct {
	bool Allocated;
	bool Looping;
	bool Playing;
	float Volume;
    ma_decoder Data;
} Subsound;

typedef enum {
	Ambience1,
	Filtration1,
	Ram1,
	Click
} Sound;

typedef struct {
	ma_device Engine;
	Subsound Data[LDE_AUDIOCOUNT];
	ma_mutex Lock;
} AUDIO;

extern AUDIO Audio;

ma_result Startup_Miniaudio();
void Shutdown_Miniaudio();
ma_result Load_Sound(const char* Path, Sound Target);
void Play_Sound(Sound Target, bool Looping);
void Terminate_Sound(Sound Target);
void Adjust_Sound(float Volume);
void Free_Sounds();