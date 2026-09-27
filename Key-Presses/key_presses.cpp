#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Initialize the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "Arrow Keys Change Color",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Default color (dark gray)
    SDL_Color currentColor = {50, 50, 50, 255}; //  the active backgroung color (Starts as dark gray)

    bool running = true;
    SDL_Event event;

    std::cout << "Press arrow keys to change color:\n";
    std::cout << "  UP    -> Red\n";
    std::cout << "  DOWN  -> Blue\n";
    std::cout << "  LEFT  -> Green\n";
    std::cout << "  RIGHT -> Yellow\n";
    std::cout << "  ESC   -> Quit\n";

    // Main loop
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        currentColor = {255, 0, 0, 255};      // Red
                        std::cout << "UP pressed -> Red\n";
                        break;
                    case SDLK_DOWN:
                        currentColor = {0, 0, 255, 255};      // Blue
                        std::cout << "DOWN pressed -> Blue\n";
                        break;
                    case SDLK_LEFT:
                        currentColor = {0, 255, 0, 255};      // Green
                        std::cout << "LEFT pressed -> Green\n";
                        break;
                    case SDLK_RIGHT:
                        currentColor = {255, 255, 0, 255};    // Yellow
                        std::cout << "RIGHT pressed -> Yellow\n";
                        break;
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                }
            }
        }

        // Clear screen with current color
        SDL_SetRenderDrawColor(renderer, 
                               currentColor.r, 
                               currentColor.g, 
                               currentColor.b, 
                               currentColor.a);
        SDL_RenderClear(renderer);

        // Present
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}