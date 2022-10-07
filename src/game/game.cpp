#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include "core/constants.h"
#include "core/entity.h"
#include "gamestates/state_manager.h"
#include "gamestates/sandbox_state.h"
#include "asset/asset_manager.h"
#include "manager/display_manager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"

using namespace dte;

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Could not init SDL: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    atexit(SDL_Quit);

    unsigned int imgflags = IMG_INIT_PNG;
    unsigned int loaded = IMG_Init(int(imgflags));
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
    window = SDL_CreateWindow("Game",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, windowFlags);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);

    DisplayManager displayManager(renderer);
    AssetManager assetManager;
    StateManager stateManager(&assetManager, &displayManager);

    SandboxState sandboxState;
    stateManager.push(&sandboxState);

    Uint32 currentTimeMs, elapsedTimeMs;
    Uint32 previousTimeMs = SDL_GetTicks();
    Uint32 accumulatorMs = 0;
    Uint32 totalTimeMs = 0;

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        currentTimeMs = SDL_GetTicks();
        elapsedTimeMs = currentTimeMs - previousTimeMs;
        previousTimeMs = currentTimeMs;

        accumulatorMs += elapsedTimeMs;

        // input
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_WINDOWEVENT) {
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        const Sint32 w = event.window.data1;
                        const Sint32 h = event.window.data2;
                        displayManager.setCachedDimensions(w, h);
                        break;
                }
            }
            stateManager.input(event);
        }

        // update
        while (accumulatorMs >= FIXED_MS_UPDATE) {
            stateManager.update();
            accumulatorMs -= FIXED_MS_UPDATE;
            totalTimeMs += FIXED_MS_UPDATE;
        }

        // load new textures
        assetManager.pumpTextures(renderer);

        // update ImGui
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        stateManager.guiUpdate();

        // render
        ImGui::Render();
        SDL_RenderClear(renderer);
        float remainderFrames = float(accumulatorMs) / float(FIXED_MS_UPDATE);
        stateManager.draw(totalTimeMs, remainderFrames);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    assetManager.shutdown();

    return 0;
}
