#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <stack>
#include <deque>
#include <unordered_map>
#include <iostream>
#include "component/block_draw.h"
#include "core/entity.h"
#include "gamestates/game_state.h"
#include "gamestates/game_load.h"
#include "asset/assets.h"
#include "asset/asset_manager.h"

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

    std::vector<Entity> entities;
    BlockDrawComponent bdc;
    Entity block(&bdc);
    entities.push_back(block);

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
            for (Entity entity : entities) {
                entity.update();
            }

            poolTimeMs = poolTimeMs - FIXED_MS_UPDATE;
        }

        // load new assets
        while (assetManager.hasNewTextureJobs()) {
            TextureJob job = assetManager.getNextTextureJob();
            std::string id = job.getImageID();
            SDL_Texture *texture = job.convertSurface(renderer);
            textures.insert(std::make_pair(id, texture));
        }

        // render
        SDL_RenderClear(renderer);
        // framesToInterpolate = poolTimeMs / FIXED_MS_UPDATE;
        for (Entity entity : entities) {
            entity.draw(renderer);
        }
        // SDL_RenderCopy(renderer, texture, src, &dst);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    return 0;
}
