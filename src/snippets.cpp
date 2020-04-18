






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