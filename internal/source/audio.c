#define MINIAUDIO_IMPLEMENTATION
#include <audio.h>

void Startup_Miniaudio() {
	Audio.Configuration = ma_engine_config_init();
	Audio.Configuration.sampleRate = 44100;
	Audio.Configuration.channels = 2;
	Audio.Configuration.periodSizeInFrames = 1024;
	ma_engine_init(&Audio.Configuration, &Audio.Audio_Engine);
}

void Shutdown_Miniaudio() {
	ma_engine_uninit(&Audio.Audio_Engine);
}

void Load_Sound(const char* Path, ma_sound* Target) {
	char Carrier[128];
	snprintf(Carrier, sizeof(Carrier), "Assets/Core/Audio/%s.wav", Path);
	ma_sound_init_from_file(&Audio.Audio_Engine, Carrier, 0, NULL, NULL, Target);
}

void Play_Sound(ma_sound* Target, bool Looping) {
	if (Looping) {
		ma_sound_set_looping(Target, MA_TRUE);
	} else {
		ma_sound_set_looping(Target, MA_FALSE);
	}
	ma_sound_start(Target);
}

void Terminate_Sound(ma_sound* Target) {
	ma_sound_stop(Target);
}

void Adjust_Sound(float Volume) {
	ma_engine_set_volume(&Audio.Audio_Engine, Volume);
}

void Free_Sound(ma_sound* Target) {
	ma_sound_uninit(Target);
}