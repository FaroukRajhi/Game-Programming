#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int POINT_SIZE = 8;
const float MOVE_SPEED = 300.0f; // pixels per second

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow(
        "SDL Keyboard Motion",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Point position (starting in the middle)
    float pointX = SCREEN_WIDTH / 2.0f;
    float pointY = SCREEN_HEIGHT / 2.0f;

    bool running = true;
    SDL_Event event;

    Uint32 lastTime = SDL_GetTicks();

    // Main loop
    while (running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        // Calculate delta time for smooth movement
        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f; // seconds
        lastTime = currentTime;

        // Get keyboard state
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // Move the point based on keys (supports diagonal movement)
        float dx = 0.0f;
        float dy = 0.0f;

        if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) {
            dx -= 1.0f;
        }
        if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
            dx += 1.0f;
        }
        if (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_W]) {
            dy -= 1.0f;
        }
        if (keystate[SDL_SCANCODE_DOWN] || keystate[SDL_SCANCODE_S]) {
            dy += 1.0f;
        }

        // Normalize diagonal movement so it isn't faster
        if (dx != 0.0f && dy != 0.0f) {
            const float invSqrt2 = 0.70710678f; // 1/sqrt(2)
            dx *= invSqrt2;
            dy *= invSqrt2;
        }

        // Apply movement
        pointX += dx * MOVE_SPEED * deltaTime;
        pointY += dy * MOVE_SPEED * deltaTime;

        // Clamp to screen boundaries
        if (pointX < 0) pointX = 0;
        if (pointX > SCREEN_WIDTH - POINT_SIZE) pointX = SCREEN_WIDTH - POINT_SIZE;
        if (pointY < 0) pointY = 0;
        if (pointY > SCREEN_HEIGHT - POINT_SIZE) pointY = SCREEN_HEIGHT - POINT_SIZE;

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // Draw the point
        SDL_SetRenderDrawColor(renderer, 255, 220, 60, 255);
        SDL_Rect pointRect = {
            static_cast<int>(pointX),
            static_cast<int>(pointY),
            POINT_SIZE,
            POINT_SIZE
        };
        SDL_RenderFillRect(renderer, &pointRect);

        // Optional: draw a crosshair at the center of the point
        SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);
        int centerX = static_cast<int>(pointX) + POINT_SIZE / 2;
        int centerY = static_cast<int>(pointY) + POINT_SIZE / 2;
        SDL_RenderDrawLine(renderer, centerX - 6, centerY, centerX + 6, centerY);
        SDL_RenderDrawLine(renderer, centerX, centerY - 6, centerX, centerY + 6);

        // Present
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}