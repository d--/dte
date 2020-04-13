#include <SDL.h>
#include <cstdlib>
#include "game.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Could not init SDL: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    atexit(SDL_Quit);

    Uint32 flags;
    flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

    SDL_Window *window;
    window = SDL_CreateWindow(
        "Tetris",                    // title
        SDL_WINDOWPOS_UNDEFINED,     // x
        SDL_WINDOWPOS_UNDEFINED,     // y
        400,                         // w
        400,                         // h
        flags                        // flags
    );

    if (window == nullptr) {
        SDL_Log("Could not create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // For time elapsed...

    // https://wiki.libsdl.org/SDL_GetTicks

    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    SDL_DestroyWindow(window);

    return 0;
}
