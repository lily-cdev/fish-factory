#define MINIAUDIO_IMPLEMENTATION
#include <audio.h>

char* Paths[LDE_AUDIOCOUNT] = {
	"Ambient/Background",
	"Machines/Filtration_Loop",
	"Machines/Ram_Loop",
	"UI/Click"
};

ma_result Startup_Miniaudio() {
	return ma_engine_init(NULL, &Audio.Engine);
}

void Shutdown_Miniaudio() {
	ma_engine_uninit(&Audio.Engine);
}

ma_result Load_Sounds() {
	for (int C1 = 0; C1 < LDE_AUDIOCOUNT; C1++) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "Assets/Core/Audio/%s.wav", Paths[C1]);
		ma_result Yield = ma_sound_init_from_file(&Audio.Engine, Carrier, 0, NULL, NULL, &(Audio.Data[C1].Data));
		if (Yield != MA_SUCCESS) {
			return Yield;
		}
		Audio.Data[C1].Volume = 0.5f;
		Audio.Data[C1].Allocated = true;
	}
	return MA_SUCCESS;
}

void Play_Sound(Sound Target, bool Looping) {
	if (!Audio.Data[Target].Allocated) {
		return;
	}
	ma_sound_set_looping(&(Audio.Data[Target].Data), (Looping) ? MA_TRUE : MA_FALSE);
	ma_sound_set_volume(&(Audio.Data[Target].Data), Audio.Data[Target].Volume);
	ma_sound_start(&(Audio.Data[Target].Data));
}

void Terminate_Sound(Sound Target) {
	if (!Audio.Data[Target].Allocated) {
		return;
	}
	ma_sound_stop(&(Audio.Data[Target].Data));
}

void Adjust_Sound(float Volume) {
	for (int C1 = 0; C1 < LDE_AUDIOCOUNT; C1++) {
		Audio.Data[C1].Volume = Volume;
	}
}

void Free_Sounds() {
	for (int C1 = 0; C1 < LDE_AUDIOCOUNT; C1++) {
		if (Audio.Data[C1].Allocated) {
			ma_sound_uninit(&(Audio.Data[C1].Data));
			Audio.Data[C1].Allocated = false;
		}
	}
}