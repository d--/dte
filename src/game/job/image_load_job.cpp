#include "image_load_job.h"

#include <utility>
#include <SDL_image.h>

namespace dte {
    ImageLoadJob::ImageLoadJob(std::string id, std::string location) :
            imageId(std::move(id)),
            imageName(std::move(location)) {}

    void ImageLoadJob::execute(AssetManager *manager) {
        // todo: remove this; pretending that images take a long time
        SDL_Delay(5000);
        std::string basePath(SDL_GetBasePath());
        std::string location(basePath + "../assets/" + imageName);
        SDL_Surface *surface = IMG_Load(location.c_str());
        if (surface == nullptr) {
            SDL_Log("Could not load image: %s\n", imageName.c_str());
            SDL_Log("Error: %s\n", IMG_GetError());
            return;
        }

        auto *textureJob = new TextureJob(imageId, surface);
        manager->submitTextureJob(textureJob);

        Uint32 variableDelay = 2;
        Uint32 delayMax = 200;
        while (!textureJob->isFinished()) {
            SDL_Delay(variableDelay);
            if (variableDelay < delayMax) {
                variableDelay *= 2;
            }
        }
    }
}
