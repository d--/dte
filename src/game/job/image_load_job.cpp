#include "image_load_job.h"

#include <utility>
#include <SDL_image.h>

namespace dte {
    ImageLoadJob::ImageLoadJob(std::string id, std::string location) :
        imageId(std::move(id)),
        imageLocation(std::move(location)) {}

    void ImageLoadJob::execute(AssetManager *manager) {
        std::string basePath(SDL_GetBasePath());
        std::string location(basePath + imageLocation);
        SDL_Surface *surface = IMG_Load(location.c_str());
        if (surface == nullptr) {
            SDL_Log("Could not load image: %s\n", imageLocation.c_str());
            SDL_Log("Error: %s\n", IMG_GetError());
            return;
        }

        manager->enqueueJob(new TextureJob(imageId, surface));
    }
}
