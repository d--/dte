






SDL_Texture* texture;
texture = SDL_CreateTextureFromSurface(renderer, surface);
if (texture == nullptr)
{
    SDL_Log("Could not create texture: %s\n", path.c_str());
    SDL_Log("Error: %s\n", SDL_GetError());
}

SDL_FreeSurface(surface);
return texture;









SDL_Surface AssetManager::loadImage(std::string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr)
    {
        SDL_Log("Could not load image: %s\n", path.c_str());
        SDL_Log("Error: %s\n", IMG_GetError());
        return nullptr;
    }
    return surface;
}






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