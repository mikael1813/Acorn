#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Application.hpp"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
//#undef main
using namespace std;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath = "../Model/SpriteSheetAcorn.png") {
    SDL_Surface* surface = IMG_Load(filePath = "../Model/SpriteSheetAcorn.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

int main(int argc, char* args[]) {

   

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Sprite Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize SDL_image for loading PNG images
    IMG_Init(IMG_INIT_PNG);

    // Load your sprite sheet
    SDL_Texture* spriteSheet = loadTexture(renderer, "../Model/SpriteSheetAcorn.png");

    // Define the dimensions of a single frame in the sprite sheet
    int frameWidth = 32;
    int frameHeight = 32;

    // Number of frames in the sprite sheet
    int numFrames = 5;

    // Set up a rectangle to represent the current frame
    SDL_Rect srcRect = { 0, 0, frameWidth, frameHeight };

    // Set up a rectangle to represent where the frame will be drawn on the window
    SDL_Rect destRect = { 500, 500, frameWidth, frameHeight };

    // Variable to keep track of the current frame
    int currentFrame = 0;

    // Main loop
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Update the source rectangle to get the next frame from the sprite sheet
        srcRect.x = currentFrame * frameWidth;

        // Draw the current frame to the window
        SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);

        // Update the window
        SDL_RenderPresent(renderer);

        // Delay for a short period to control the animation speed
        SDL_Delay(100);

        // Move to the next frame
        currentFrame = (currentFrame + 1) % numFrames;
    }

    // Cleanup and exit
    SDL_DestroyTexture(spriteSheet);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

