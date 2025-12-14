#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int TILE_SIZE = 32;

int main(int argc, char* args[]) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    
    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "My First Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    
    // Create renderer (this draws stuff)
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Game variables
    int playerX = 300;
    int playerY = 200;
    int speed = 5;
    
    int coinX = 500;
    int coinY = 300;
    
    int score = 0;
    bool running = true;
    SDL_Event event;
    
    // Game loop
    while(running) {
        // Handle events (keyboard, mouse, etc)
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
        }
        
        // Get keyboard state
        const Uint8* keyState = SDL_GetKeyboardState(NULL);
        
        // Move player
        if(keyState[SDL_SCANCODE_W]) {
            playerY -= speed;  // Move up
        }
        if(keyState[SDL_SCANCODE_S]) {
            playerY += speed;  // Move down
        }
        if(keyState[SDL_SCANCODE_A]) {
            playerX -= speed;  // Move left
        }
        if(keyState[SDL_SCANCODE_D]) {
            playerX += speed;  // Move right
        }
        
        // Keep player on screen
        if(playerX < 0) playerX = 0;
        if(playerX > SCREEN_WIDTH - TILE_SIZE) playerX = SCREEN_WIDTH - TILE_SIZE;
        if(playerY < 0) playerY = 0;
        if(playerY > SCREEN_HEIGHT - TILE_SIZE) playerY = SCREEN_HEIGHT - TILE_SIZE;
        
        // Check collision with coin (simple rectangle collision)
        if(playerX < coinX + TILE_SIZE &&
           playerX + TILE_SIZE > coinX &&
           playerY < coinY + TILE_SIZE &&
           playerY + TILE_SIZE > coinY) {
            score++;
            // Respawn coin
            coinX = rand() % (SCREEN_WIDTH - TILE_SIZE);
            coinY = rand() % (SCREEN_HEIGHT - TILE_SIZE);
        }
        
        // Clear screen (black background)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // Draw player (blue rectangle)
        SDL_Rect playerRect = {playerX, playerY, TILE_SIZE, TILE_SIZE};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue
        SDL_RenderFillRect(renderer, &playerRect);
        
        // Draw coin (yellow rectangle)
        SDL_Rect coinRect = {coinX, coinY, TILE_SIZE, TILE_SIZE};
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow
        SDL_RenderFillRect(renderer, &coinRect);
        
        // Update screen
        SDL_RenderPresent(renderer);
        
        // Control frame rate (60 FPS)
        SDL_Delay(16);
    }
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    cout << "Final Score: " << score << endl;
    
    return 0;
}