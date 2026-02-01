#define MINIAUDIO_IMPLEMENTATION
#include <audio.h>

int Startup_Miniaudio() {
	Audio.Configuration = ma_engine_config_init();
	Audio.Configuration.sampleRate = 44100;
	Audio.Configuration.channels = 2;
	//Audio.Configuration.playb
	Audio.Configuration.periodSizeInFrames = 1024;
	return ma_engine_init(&Audio.Configuration, &Audio.Audio_Engine);
}

void Shutdown_Miniaudio() {
	ma_engine_uninit(&Audio.Audio_Engine);
}

void Load_Sound(const char* Path, Sound* Target) {
	char Carrier[128];
	snprintf(Carrier, sizeof(Carrier), "Assets/Core/Audio/%s.wav", Path);
	if (ma_sound_init_from_file(&Audio.Audio_Engine, Carrier, 0, NULL, NULL, &(Target->Data)) != MA_SUCCESS) {
		//error l8er
		puts("oe");
	}
	Target->Allocated = true;
}

void Play_Sound(Sound* Target, bool Looping) {
	ma_sound_set_looping(&(Target->Data), (Looping) ? MA_TRUE : MA_FALSE);
	ma_sound_start(&(Target->Data));
}

void Terminate_Sound(Sound* Target) {
	ma_sound_stop(&(Target->Data));
}

void Adjust_Sound(float Volume) {
	ma_engine_set_volume(&Audio.Audio_Engine, Volume);
}

void Free_Sound(Sound* Target) {
	if (Target->Allocated) {
		ma_sound_uninit(&(Target->Data));
		Target->Allocated = false;
	}
}