#pragma once
#include <miniaudio.h>
#include <string>

class Audio {
public:
	ma_engine Audio_Engine = { 0 };
	ma_engine_config Audio_Configuration = { 0 };
	ma_sound Primary_Ambience = { 0 };
	ma_sound Filtration_Loop = { 0 };
	ma_sound Ram_Loop = { 0 };
	ma_sound Click = { 0 };
    void Startup();
    void Shutdown();
    void Load(ma_sound* Target, std::string Path);
    void Play(ma_sound* Target, bool Looping);
    void Terminate(ma_sound* Target);
    void Set_Volume(float Volume);
    void Free(ma_sound* Target);
};

extern Audio Audio_Access;