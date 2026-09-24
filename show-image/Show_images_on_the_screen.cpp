#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* getWelcomeToSDL = NULL;

// Starts up SDL library and create a window

bool init()
{
    // Initialize flag

    bool success = true;

    // Initilaize SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Could not inialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        // Create a window

        gWindow = SDL_CreateWindow("SDL Testing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

        if(gWindow == NULL)
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

// Load Media

bool loadMedia()
{

    // Loading success flag

    bool success = true;

    // Load splash image

    getWelcomeToSDL = SDL_LoadBMP("/home/faroukrajhi/Desktop/Game-Programming/image.bmp");

    if(getWelcomeToSDL == NULL)
    {
        printf("Unable to load image %s! SDL Error: %s\n", "Game-Programming/image.png", SDL_GetError());
        success = false;
    }

    return success;
}

//Frees media and shuts down SDL to prevent memory leaks

void close()
{
    // Deallocate Surface
    SDL_FreeSurface(getWelcomeToSDL);
    getWelcomeToSDL = NULL;
    // Destroy  Window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;


    // Leave SDL Subsystems

    SDL_Quit();


}

int main(int argc, char* args[])
{
    // Initialize SDL and create a windo

    if(!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Loading Media

        if(!loadMedia())
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Apply the image
            SDL_BlitSurface( getWelcomeToSDL, NULL, gScreenSurface, NULL );
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );

            //Hack to get window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

        }
    }


    // Free resources and close SDL
    close();


    return 0;
}
