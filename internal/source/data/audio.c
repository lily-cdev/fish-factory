#include <data.h>

AUDIO Audio = { };

char* Paths[ktn_audio_ct] = {
	"Ambient/Background",
	"Machines/Filtration_Loop",
	"Machines/Ram_Loop",
	"UI/Click"
};

void Startup_Miniaudio() {
	ma_result Yield = ma_engine_init(NULL, &Audio.Engine);
	if (Yield != MA_SUCCESS) {
		char Carrier[512];
		snprintf(Carrier, sizeof(Carrier), "could not load Miniaudio; %s", ma_result_description(Yield));
		ktn_jump(I_No_Miniaudio, Carrier);
	}
}

void Shutdown_Miniaudio() {
	ma_engine_uninit(&Audio.Engine);
}

void Load_Sounds() {
	for (int C1 = 0; C1 < ktn_audio_ct; C1++) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "Assets/Core/Audio/%s.wav", Paths[C1]);
		ma_result Yield = ma_sound_init_from_file(&Audio.Engine, Carrier, 0, NULL, NULL, &(Audio.Data[C1].Data));
		if (Yield != MA_SUCCESS) {
			char Carrier[512];
			snprintf(Carrier, sizeof(Carrier), "could not load a sound; %s", ma_result_description(Yield));
			ktn_jump(I_No_Sound, Carrier);
		}
		Audio.Data[C1].Volume = 0.5f;
		Audio.Data[C1].Allocated = true;
	}
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
	for (int C1 = 0; C1 < ktn_audio_ct; C1++) {
		Audio.Data[C1].Volume = Volume;
	}
}

void Free_Sounds() {
	for (int C1 = 0; C1 < ktn_audio_ct; C1++) {
		if (Audio.Data[C1].Allocated) {
			ma_sound_uninit(&(Audio.Data[C1].Data));
			Audio.Data[C1].Allocated = false;
		}
	}
}