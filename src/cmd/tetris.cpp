#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include "game.h"

// todo: tune this
#define FIXED_MS_UPDATE 16

SDL_Texture* loadTexture(std::string path, SDL_Renderer *renderer) {
    SDL_Texture* texture;

    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Could not load image: %s\n", path.c_str());
        SDL_Log("Error: %s\n", IMG_GetError());
        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr)
    {
        SDL_Log("Could not create texture: %s\n", path.c_str());
        SDL_Log("Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    return texture;
}

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Could not init SDL: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    atexit(SDL_Quit);

    int imgflags = IMG_INIT_PNG;
    int loaded;
    loaded = IMG_Init(imgflags);
    if ((loaded & imgflags) != imgflags) {
        SDL_Log("Could not init SDL_image: %s\n", IMG_GetError());
    }
    atexit(IMG_Quit);

    Uint32 windowFlags;
    windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

    SDL_Window *window;
    window = SDL_CreateWindow("Tetris",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        400, 400, windowFlags);
    if (window == nullptr) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Could not create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture;
    std::string filename = "block.png";
    texture = loadTexture(filename, renderer);
    if (texture == nullptr) {
        SDL_Log("Could not load image: %s\n", filename.c_str());
        SDL_Log("Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Rect* src;
    SDL_Rect dst;
    src = nullptr;
    dst.x = (400 - 256) / 2;
    dst.y = (400 - 256) / 2;
    dst.w = 256;
    dst.h = 256;
    SDL_SetTextureColorMod(texture, Uint8(0xFF), Uint8(0x00), Uint8(0xFF));

    Uint32 currentTimeMs, elapsedTimeMs = 0;
    Uint32 previousTimeMs = SDL_GetTicks();
    Uint32 poolTimeMs = 0;

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        currentTimeMs = SDL_GetTicks();
        elapsedTimeMs = currentTimeMs - previousTimeMs;
        previousTimeMs = currentTimeMs;
        poolTimeMs = poolTimeMs + elapsedTimeMs;

        // input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // update
        while (poolTimeMs > FIXED_MS_UPDATE) {
            // update()
            poolTimeMs = poolTimeMs - FIXED_MS_UPDATE;
        }

        /// render
        // framesToInterpolate = poolTimeMs / FIXED_MS_UPDATE;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, src, &dst);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
