#include "Texture.h"

bool Texture::create(SDL_Renderer *renderer, int width, int height)
{
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!texture)
    {
        SDL_Log("Could not create texture: %s", SDL_GetError());
        return false;
    }

    SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
    return true;
}

void Texture::update(const uint8_t *displayBuffer)
{
    for (int i = 0; i < Display::SIZE; ++i)
    {
        pixels[i] = displayBuffer[i] ? 0xFFFFFFFF : 0x000000FF;
    }

    SDL_UpdateTexture(texture, nullptr, &pixels, Display::WIDTH * sizeof(uint32_t));
}