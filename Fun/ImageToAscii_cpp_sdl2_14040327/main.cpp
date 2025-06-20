#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
using namespace std;

//const string asciiChars = "`^\\\",:;Il!i~+_-?][}{1)(|\\\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

const string asciiChars = " ,:;+*i!?t%B@$";

int mapRanged(int, int, int, int, int);

int main(int argc, char* argv[]) {
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        cout << "SDL_Image init error: " << IMG_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    SDL_Surface* surface = IMG_Load("/home/parsa/Downloads/images (1).jpeg");

    if (!surface) {
        cout << "Failed to load image: " << IMG_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
    }

    Uint32 *pixels = (Uint32 *)surface->pixels;
    int width = surface->w * 0.75;
    int height = surface->h;
    int pitch = surface->pitch / 4;
//    cout << pitch << endl;

    for (int y = 0; y < height; y+=2) {
        for (int x = 0; x < width; x++) {
            Uint32 pixel = pixels[y*pitch + x];
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixel, surface->format, &r, &g, &b, &a);

            int grayPixel = static_cast<int>((r + g + b)/3);
            cout << asciiChars[mapRanged(grayPixel, 0, 255, 0, 14)];
        }
        cout << endl;
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}

int mapRanged(int value, int oldMin, int oldMax, int newMin, int newMax) {
    return (int) ceil(newMin + (value - oldMin) * (newMax - newMin) / (oldMax - oldMin));
}