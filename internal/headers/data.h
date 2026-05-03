#pragma once
#include <core.h>
#include <prepping.h>
#include <connectables.h>
#include <items.h>

typedef struct {
	bool Allocated;
	float Volume;
	ma_sound Data;
} Subsound;

typedef struct {
	ma_engine Engine;
	Subsound Data[ktn_audio_ct];
} AUDIO;

extern AUDIO Audio;

void Startup_Miniaudio();
void Shutdown_Miniaudio();
void Load_Sounds();
void Play_Sound(Sound Target, bool Looping);
void Terminate_Sound(Sound Target);
void Adjust_Sound(float Volume);
void Free_Sounds();
void Get_Filesizes();
bool Save_Data(int Slot);
bool Load_Data(int Slot);
bool Save_Settings();
void Load_Settings();
void Clear_Settings();
void Recalibrate_Settings();
void Reset_Statistics();
void Reset_Tile(Point Pos);
void Reload_All(bool Initialized);