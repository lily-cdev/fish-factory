#define MINIAUDIO_IMPLEMENTATION
#include <audio.h>
#define get_frame_bytes ma_get_bytes_per_frame
#define read_frames ma_decoder_read_pcm_frames
#define seek_frames ma_decoder_seek_to_pcm_frame

void Callback(ma_device* Device, void* Output, void* Input, ma_uint32 Frames) {
	memset(Output, 0, get_frame_bytes(Device->playback.format, Device->playback.channels) * Frames);
	ma_mutex_lock(&Audio.Lock);
	for (int C1 = 0; C1 < LDE_AUDIOCOUNT; C1++) {
		if (Audio.Data[C1].Playing) {
			ma_uint64 Subframes;
			read_frames(&(Audio.Data[C1].Data), Output, Frames, &Subframes);
			for (int C2 = 0; C2 < Subframes * Device->playback.channels; C2++) {
				Output[C2] *= Audio.Data[C1].Volume;
			}
			if (Subframes < Frames) {
				(Audio.Data[C1].Looping) ? seek_frames(&(Audio.Data[C1].Data), 0) : Audio.Data[C1].Playing = false;
			}
		}
	}
	ma_mutex_unlock(&Audio.Lock);
	(void)Input;
}

ma_result Startup_Miniaudio() {
	ma_device_config Config = ma_device_config_init(ma_device_type_playback);
	Config.playback.format = LDE_FORMAT;
	Config.playback.channels = LDE_CHANNELS;
	Config.sampleRate = LDE_SAMPLERATE;
	Config.dataCallback = Callback;
	ma_result Yield = ma_device_init(NULL, &Config, &Audio.Engine);
	if (Yield != MA_SUCCESS) {
		return Yield;
	}
	Yield = ma_mutex_init(&Audio.Lock);
	if (Yield != MA_SUCCESS) {
		return Yield;
	}
	return ma_device_start(&Audio.Engine);
}

void Shutdown_Miniaudio() {
	ma_device_uninit(&Audio.Audio_Engine);
	ma_mutex_uninit(&Audio.Lock);
}

ma_result Load_Sound(const char* Path, Sound Target) {
	char Carrier[128];
	snprintf(Carrier, sizeof(Carrier), "Assets/Core/Audio/%s.wav", Path);
	Audio.Data[Target].Volume = 0.5f;
	Audio.Data[Target].Playing = false;
	Audio.Data[Target].Looping = false;
	Audio.Data[Target].Allocated = true;
	ma_decoder_config Config = ma_decoder_config_init(LDE_FORMAT, LDE_CHANNELS, LDE_SAMPLERATE);
	return ma_decoder_init_file(Carrier, &Config, &(Audio.Data[Target].Data));
}

void Play_Sound(Sound Target, bool Looping) {
	ma_mutex_lock(&Audio.Lock);
	Audio.Data[Target].Looping = Looping;
	Audio.Data[Target].Playing = true;
	ma_decoder_seek_to_pcm_frame(&(Audio.Data[Target].Data), 0);
	ma_mutex_unlock(&Audio.Lock);
}

void Terminate_Sound(Sound Target) {
	ma_mutex_lock(&Audio.Lock);
	Audio.Data[Target].Playing = false;
	ma_mutex_unlock(&Audio.Lock);
}

void Adjust_Sound(float Volume) {
	ma_mutex_lock(&Audio.Lock);
	for (int C1 = 0; C1 < LDE_AUDIOCOUNT; C1++) {
		Audio.Data[C1].Volume = Volume;
	}
	ma_mutex_unlock(&Audio.Lock);
}

void Free_Sounds() {
	for (int C1 = 0; C1 < LDE_AUDIOCOUNT; C1++) {
		if (Audio.Data[C1].Allocated) {
			ma_decoder_uninit(&(Audio.Data[C1].Data));
			Audio.Data[C1].Allocated = false;
		}
	}
}