#include "SDL.h"
#include "FileLoader.hpp"

SDL_Surface* load_surface(std::string path) {
    SDL_Surface* image_surface = SDL_LoadBMP(path.c_str());

    if (!image_surface)
        return 0;

    return image_surface;
}