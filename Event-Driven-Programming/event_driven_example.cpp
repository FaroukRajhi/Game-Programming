#include <SDL2/SDL.h>
#include <stdio.h>

// Define screen dimensions 

const int WIDTH = 800;
const int HEIGHT = 1000;

SDL_Window* window = NULL;

SDL_Surface* surface = NULL;

// The image that will be loaded and show up on the screen
SDL_Surface* gXOut = NULL;

// Booting up SDL library and creating window

bool init()
{
    // Initializing flag
    bool success = true;

    //Starts up SDL
    if(SDL_Init( SDL_INIT_VIDEO) < 0)
    {
        printf("SDL library could not initialize. SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Creating the window

        window = SDL_CreateWindow("Event-Driven Programming Example",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("window could not be created. SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            surface = SDL_GetWindowSurface(window);
        }
    }

    return 0;
}

// Media Loading

bool mediaLoad()
{
    bool success = true;

    // Load Image

    gXOut = SDL_LoadBMP("/home/faroukrajhi/Desktop/Game-Programming/Event-Driven-Programming/wolf.bmp");

    if(gXOut == NULL)
    {
        printf("Unbale to load image %s. SDL Error: %s\n", "wolf.bmp", SDL_GetError());
        success = false;

    }

    return success;
}

// Free resources

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gXOut );
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow( window );
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{

    // Initialize SDL library and create window

    if(!init())
    {
        printf("Failed to start up !\n");
    }
    else
    {
        // Media Loading

        if(!mediaLoad())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            bool quit = false;

            // Event Handler

            SDL_Event e;

            while(!quit)
            {
                // handle events on queue
                while(SDL_PollEvent(&e) != 0)
                {

                    // User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;  
                    }
                }


                // Apply the image

                SDL_BlitSurface(gXOut,NULL, surface, NULL);

                // Update surface

                SDL_UpdateWindowSurface(window);


            }
        
        }
    }

    close();
    return 0;
}