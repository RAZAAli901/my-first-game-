# My First SDL2 Game

A simple 2D game built with C++ and SDL2 where a player collects coins.

## How to Run

1.  **Prerequisites**:
    *   Windows with MSYS2 installed.
    *   MinGW-w64 GCC and SDL2 libraries.

2.  **Build and Run**:
    *   Open a terminal in this directory.
    *   Run the build script:
        ```powershell
        ./build.ps1
        ```
    *   Alternatively, compile manually:
        ```bash
        g++ sdl2.cpp -o game.exe -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -lmingw32 -lSDL2main -lSDL2
        ./game.exe
        ```

## How It Works

The game is written in C++ using the SDL2 library. Here's a breakdown of the core components:

*   **Initialization**: We initialize SDL video subsystem and create a window (`SDL_CreateWindow`) and a renderer (`SDL_CreateRenderer`). The renderer is what we use to draw to the screen.
*   **Game Loop**: The `while(running)` loop keeps the game alive. In every iteration (frame), we:
    1.  **Handle Events**: Check if the user closed the window (`SDL_QUIT`).
    2.  **Input**: Check keyboard state (`SDL_GetKeyboardState`) to move the player.
    3.  **Logic**: Update player position, keep them in bounds, and check for collisions with the coin.
    4.  **Render**: Clear the screen, draw the objects, and swap the buffers (`SDL_RenderPresent`) to show the new frame.

## How Graphics Are Created

Unlike modern games that use complex 3D models or sprite images, this game uses **procedural geometric rendering**. We don't load any external image files (like .png or .jpg). Instead, we instruct the graphics card to draw colored rectangles directly.

### The Code Behind the Graphics

1.  **The Player (Blue Square)**:
    ```cpp
    // Define the rectangle's position (x, y) and size (32x32)
    SDL_Rect playerRect = {playerX, playerY, 32, 32};
    
    // Set the drawing color to Blue (Red:0, Green:0, Blue:255, Alpha:255)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    
    // Command the renderer to fill the rectangle with the current color
    SDL_RenderFillRect(renderer, &playerRect);
    ```

2.  **The Coin (Yellow Square)**:
    ```cpp
    SDL_Rect coinRect = {coinX, coinY, 32, 32};
    // Set color to Yellow (Red:255, Green:255, Blue:0)
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &coinRect);
    ```

3.  **The Background**:
    We clear the screen with Black at the start of every frame:
    ```cpp
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    SDL_RenderClear(renderer);
    ```

This method is very fast and efficient for simple games and prototypes!
