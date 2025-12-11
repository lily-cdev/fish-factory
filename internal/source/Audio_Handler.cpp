#define MINIAUDIO_IMPLEMENTATION
#include <Audio_Handler.h>

void Audio::Startup() {
    Audio_Configuration = ma_engine_config_init();
	Audio_Configuration.sampleRate = 44100;
	Audio_Configuration.channels = 2;
	Audio_Configuration.periodSizeInFrames = 1024;
	ma_engine_init(&Audio_Configuration, &Audio_Engine);
}

void Audio::Shutdown() {
	ma_engine_uninit(&Audio_Engine);
}

void Audio::Load(ma_sound* Target, std::string Path) {
    ma_sound_init_from_file(&Audio_Engine, Path.c_str(),
        0, NULL, NULL, Target);
}

void Audio::Play(ma_sound* Target, bool Looping) {
    if (Looping) {
        ma_sound_set_looping(Target, MA_TRUE);
    } else {
        ma_sound_set_looping(Target, MA_FALSE);
    }
    ma_sound_start(Target);
}

void Audio::Terminate(ma_sound* Target) {
    ma_sound_stop(Target);
}

void Audio::Set_Volume(float Volume) {
    ma_engine_set_volume(&Audio_Engine, Volume);
}

void Audio::Free(ma_sound* Target) {
    ma_sound_uninit(Target);
}