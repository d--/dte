#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <stack>
#include <deque>
#include <unordered_map>
#include <iostream>
#include "gamestates/game_state.h"
#include "gamestates/game_load.h"
#include "asset/assets.h"
#include "asset/asset_manager.h"
#include "asset/texture_job.h"

using namespace dte;

// todo: tune this
#define FIXED_MS_UPDATE 16

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
        SDL_Quit();
        return 1;
    }
    atexit(IMG_Quit);

    loaded = TTF_Init();
    if (loaded == -1) {
        SDL_Log("Could not init SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    atexit(TTF_Quit);

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

    AssetManager assetManager;

    std::stack<GameState *> gameStates;
    GameLoad loading = GameLoad(&assetManager);
    gameStates.push(&loading);

    assetManager.loadImages();
    std::unordered_map<std::string, SDL_Texture *> textures;

    TTF_Font *font = TTF_OpenFont("assets/Philosopher-Regular.ttf", 28);
    if (font == nullptr) {
        SDL_Log("Could not load font: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *textSurface = TTF_RenderText_Blended(font,
        "Successfully displaying text!",
        SDL_Color{Uint8(0xFF), Uint8(0xFF), Uint8(0xFF), Uint8(0xFF)});
    if (textSurface == nullptr) {
        SDL_Log("Could not render text surface: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Rect textDest{0, 0, textSurface->w, textSurface->h};
    textDest.x = (400 - textDest.w) / 2;
    textDest.y = (400 - textDest.h) / 2;

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer,
        textSurface);
    if (textTexture == nullptr) {
        SDL_Log("Could not convert text surface: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(textSurface);

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
            gameStates.top()->update();
            poolTimeMs = poolTimeMs - FIXED_MS_UPDATE;
        }

        // load new assets
        while (assetManager.hasNewTextureJobs()) {
            TextureJob job = assetManager.getNextTextureJob();
            std::string id = job.getImageID();
            SDL_Texture *texture = job.convertSurface(renderer);
            textures.insert(std::make_pair(id, texture));
        }

        /// render
        // framesToInterpolate = poolTimeMs / FIXED_MS_UPDATE;
        SDL_RenderClear(renderer);
        // for each renderable, rendercopy
        for (struct asset_image image : assetImages) {
            if (textures.count(image.id) > 0) {
                SDL_RenderCopy(renderer, textures.at(image.id),
                    nullptr, nullptr);
            }
        }
        SDL_RenderCopy(renderer, textTexture, nullptr, &textDest);
        // SDL_RenderCopy(renderer, texture, src, &dst);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
