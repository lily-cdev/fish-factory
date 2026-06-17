#include <core.h>
#define TRANSPARENT 254
#define BITSPERPIXEL 24
#define HEADERSIZE 54

typedef unsigned char byte;

int32_t Read_Byte4(byte* Data, uint64_t Position) {
	int32_t Yield = 0;
	for (uint8_t C1 = 0; C1 < 4; C1++) {
		Yield |= Data[C1 + Position] << (C1 * 8);
	}
	return Yield;
}

void Save_BMP(const char* Path, SDL_Surface* Carrier) {
	FILE* Image = fopen(Path, "wb");
	const SDL_PixelFormatDetails* Details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	fputc('B', Image);
	fputc('M', Image);
	uint32_t Size = (Carrier->w * Carrier->h * 3) + HEADERSIZE;
	fwrite(&Size, sizeof(uint32_t), 1, Image);
	uint16_t Zero = 0;
	fwrite(&Zero, sizeof(uint16_t), 1, Image);
	fwrite(&Zero, sizeof(uint16_t), 1, Image);
	uint32_t Offset = HEADERSIZE;
	fwrite(&Offset, sizeof(uint32_t), 1, Image);
	uint32_t Subsize = 40;
	fwrite(&Subsize, sizeof(uint32_t), 1, Image);
	int32_t Formatted_Width = Carrier->w;
	fwrite(&Formatted_Width, sizeof(int32_t), 1, Image);
	int32_t Formatted_Height = Carrier->h;
	fwrite(&Formatted_Height, sizeof(int32_t), 1, Image);
	uint16_t Planes = 1;
	fwrite(&Planes, sizeof(uint16_t), 1, Image);
	uint16_t Formatted_BPP = BITSPERPIXEL;
	fwrite(&Formatted_BPP, sizeof(uint16_t), 1, Image);
	uint32_t Compression = 0;
	fwrite(&Compression, sizeof(uint32_t), 1, Image);
	uint32_t Large_Zero = 0;
	fwrite(&Large_Zero, sizeof(uint32_t), 1, Image);
	int32_t PPM = 2835;
	fwrite(&PPM, sizeof(int32_t), 1, Image);
	fwrite(&PPM, sizeof(int32_t), 1, Image);
	fwrite(&Large_Zero, sizeof(uint32_t), 1, Image);
	fwrite(&Large_Zero, sizeof(uint32_t), 1, Image);
	SDL_LockSurface(Carrier);
	for (int X = 0; X < Carrier->w; X++) {
		for (int Y = 0; Y < Carrier->h; Y++) {
			uint32_t* Pixels = (uint32_t*)Carrier->pixels;
			SDL_Color Color = { };
			SDL_GetRGBA(Pixels[((Carrier->h - Y - 1) * Carrier->w) + X], Details, NULL, &Color.r, &Color.g, &Color.b, &Color.a);
			if (Color.a == SDL_ALPHA_TRANSPARENT) {
				Color.r = TRANSPARENT;
				Color.g = TRANSPARENT;
				Color.b = TRANSPARENT;
			}
			fputc(Color.b, Image);
			fputc(Color.g, Image);
			fputc(Color.r, Image);
		}
	}
	SDL_UnlockSurface(Carrier);
	fclose(Image);
}

SDL_Surface* Load_BMP(const char* Path) {
	FILE* Image = fopen(Path, "rb");
	if (Image == NULL) {
		return NULL;
	}
	fseek(Image, 0, SEEK_END);
	uint64_t Length = ftell(Image);
	rewind(Image);
	byte* Data = calloc(Length, sizeof(byte));
	fread(Data, sizeof(byte), Length, Image);
	if (Data[0] != 'B' || Data[1] != 'M') {
		ktn_free(Data);
		return NULL;
	}
	int Width = Read_Byte4(Data, 18);
	int Height = Read_Byte4(Data, 22);
	SDL_Surface* Yield = SDL_CreateSurface(Width, Height, SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Yield);
	uint32_t* Pixels = (uint32_t*)Yield->pixels;
	uint64_t Row_Size = (uint64_t)(ceilf(Width * BITSPERPIXEL * 0.03125f) * 4.0f);
	uint64_t Index = (uint64_t)HEADERSIZE;
	uint8_t Opacity;
	const SDL_PixelFormatDetails* Details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	for (int Y = 0; Y < Height; Y++) {
		for (int X = 0; X < Width; X++) {
			Opacity = SDL_ALPHA_OPAQUE;
			if (Data[Index + 2] == TRANSPARENT && Data[Index + 1] == TRANSPARENT && Data[Index] == TRANSPARENT) {
				Opacity = SDL_ALPHA_TRANSPARENT;
			}
			Pixels[((Height - Y - 1) * Width) + X] = SDL_MapRGBA(Details, NULL, Data[Index + 2], Data[Index + 1], Data[Index],
				Opacity);
			Index += 3;
		}
		Index += Row_Size - (Width * 3);
	}
	SDL_UnlockSurface(Yield);
	fclose(Image);
	ktn_free(Data);
	return Yield;
}