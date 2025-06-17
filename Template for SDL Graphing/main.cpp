#include <iostream>
#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

// SCREEN DIMENSIONS  (COSTUMIZED)
const int screen_width = 1000;
const int screen_height = 700;

// CHECK QUIT OR NOT
bool game_quit = false;

// SDL OBJECTS
SDL_Window* window;
SDL_Renderer * renderer;
SDL_Surface* window_surface;

//FUNCTIONS
int initialize_window();
bool check_quit();


int main (int argv,char* argc[]) {
    initialize_window();

    check_quit();

    // ALWAYS WE USING THIS AFTER EVERY PROGRAMING WITH SDL
    SDL_RenderPresent(renderer);
    return 0;
}


// CHECKING IF QUITING
bool check_quit() {
    SDL_Event quit_event;

    while (SDL_PollEvent(&quit_event) != 0) {
        if (quit_event.type == SDL_QUIT) {
            return true;
        }
    }

    return false;
}


// INITIALIZING WINDOW OBJECTS
int initialize_window() {
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    SDL_Init( SDL_flags );
    window = SDL_CreateWindow("The Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RaiseWindow(window);
    window_surface = SDL_GetWindowSurface(window);
    SDL_FillRect(window_surface, NULL, SDL_MapRGB(window_surface->format, 255, 255, 255));
    SDL_RenderClear(renderer);
    SDL_UpdateWindowSurface(window);

    // BISHTAR BARAYE FULLSCREEN MODE HAST
//    SDL_DisplayMode DM;
//    SDL_GetCurrentDisplayMode(0, &DM);
    return 0;
}


/* Add to Cmake project

target_link_libraries(${PROJECT_NAME} -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer)

*/