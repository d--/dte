#include "text_load_job.h"

#include <utility>
#include <SDL_ttf.h>

namespace dte {
    TextLoadJob::TextLoadJob(std::string id, std::string font, std::string text,
            int pt, Uint8 r, Uint8 g, Uint8 b, Uint8 a) :
            id(std::move(id)),
            font(std::move(font)),
            text(std::move(text)),
            pt(pt),
            r(r), g(g), b(b), a(a) {}

    void TextLoadJob::execute(AssetManager *manager) {
        std::string location = "../assets/" + font;
        TTF_Font *ttfFont = TTF_OpenFont(location.c_str(), pt);
        if (ttfFont == nullptr) {
            SDL_Log("Could not load font: %s\n", TTF_GetError());
        }

        SDL_Surface *textSurface = TTF_RenderText_Blended(ttfFont,
            text.c_str(), SDL_Color{r, g, b, a});

        if (textSurface == nullptr) {
            SDL_Log("Could not render text surface: %s\n", TTF_GetError());
        }
        manager->enqueueJob(new TextureJob(id, textSurface));
    }
}

