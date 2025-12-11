#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

extern SDL_ScaleMode Scaling_Quality;

inline SDL_Texture* SDL_GenerateTexture(SDL_Renderer* Renderer, SDL_PixelFormat Format,
    SDL_TextureAccess Access, int Width, int Height) {
    SDL_Texture* Texture = SDL_CreateTexture(Renderer, Format, Access, Width, Height);
    SDL_SetTextureScaleMode(Texture, Scaling_Quality);
    return Texture;
}

inline SDL_Texture* SDL_GenerateTextureFromSurface(SDL_Renderer* Renderer, SDL_Surface* Surface) {
    SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
    SDL_SetTextureScaleMode(Texture, Scaling_Quality);
    return Texture;
}

inline SDL_Texture* IMG_GenerateTexture(SDL_Renderer* Renderer, const char* Path) {
    SDL_Texture* Texture = IMG_LoadTexture(Renderer, Path);
    SDL_SetTextureScaleMode(Texture, Scaling_Quality);
    return Texture;
}