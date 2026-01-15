#include <core.h>
#define byte unsigned char
#define TRANSPARENT 254
#define BITSPERPIXEL 24

int32_t Read_Byte4(byte* Data, uint64_t Position) {
    int32_t Yield = 0;
    for (uint8_t Counter = 0; Counter < 4; Counter++) {
        Yield |= Data[Counter + Position] << (Counter * 8);
    }
    return Yield;
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
    if (Data[0] != 0x42 || Data[1] != 0x4D) {
        free_c(Data);
        return NULL;
    }
    int Width = Read_Byte4(Data, 18);
    int Height = Read_Byte4(Data, 22);
    SDL_Surface* Yield = SDL_CreateSurface(Width, Height, SDL_PIXELFORMAT_RGBA8888);
    SDL_LockSurface(Yield);
    uint32_t* Pixels = (uint32_t*)Yield->pixels;
    uint64_t Row_Size = ceil(Width * BITSPERPIXEL * 0.03125f) * 4;
    uint64_t Index = 54;
    uint8_t Opacity;
    const SDL_PixelFormatDetails* Details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
    for (int Y = 0; Y < Height; Y++) {
        for (int X = 0; X < Width; X++) {
            Opacity = SDL_ALPHA_OPAQUE;
            if (Data[Index + 2] == TRANSPARENT && Data[Index + 1] == TRANSPARENT && Data[Index] == TRANSPARENT) {
                Opacity = SDL_ALPHA_TRANSPARENT;
            }
            Pixels[((Height - Y - 1) * Width) + X] = SDL_MapRGBA(
                Details, NULL, Data[Index + 2],
                Data[Index + 1], Data[Index], Opacity);
            Index += 3;
        }
        Index += Row_Size - (Width * 3);
    }
    SDL_UnlockSurface(Yield);
    fclose(Image);
    free_c(Data);
    return Yield;
}