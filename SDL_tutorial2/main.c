#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "main.h"

int main(int argc, char* argv[])
{
    SDL_Rect rect;
    rect.x = 20;
    rect.y = 0;

    printf("Hello world!\n");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);   // 初始化

    SDL_Window* window = SDL_CreateWindow("Main",      // 标题
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,    // 右上角的位置
                                           WINDOW_WIDTH, WINDOW_HEIGHT,    // 大小
                                           SDL_WINDOW_SHOWN);   // 模式

    SDL_Surface* surface = SDL_GetWindowSurface(window);

    SDL_Surface* img = IMG_Load("a1.png");



    SDL_BlitSurface(img, NULL, surface, NULL);
    //SDL_UpdateWindowSurface(window);
    SDL_BlitSurface(img, NULL, surface, &rect);
    SDL_UpdateWindowSurface(window);

    SDL_Delay(5000);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(img);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
