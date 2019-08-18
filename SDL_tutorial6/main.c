#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "main.h"

int main(int argc, char* argv[])
{
    printf("SDL Init...\n");

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);   // 初始化

    printf("SDL Create Window...\n");

    /* 创建窗口 */
    SDL_Window* window = SDL_CreateWindow("Main", WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    printf("SDL Create Renderer...\n");

    SDL_Renderer* pRend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND); // 设置渲染模式

    SDL_RenderClear(pRend); // 清屏

    printf("SDL Is Loading Picture...\n");
    SDL_Surface* catSurface = IMG_Load("cat.jpg");     // 加载猫咪的图片
    SDL_Texture* catTexture = SDL_CreateTextureFromSurface(pRend, catSurface);  // 创建猫咪的Texture

    SDL_Surface* blackSurface = IMG_Load("black.jpg");     // 加载黑色背景的图片
    SDL_Texture* blackTexture = SDL_CreateTextureFromSurface(pRend, blackSurface);  // 创建黑色背景的Texture

    SDL_SetTextureBlendMode(catTexture, SDL_BLENDMODE_BLEND); // 把catTexture设置成可以支持半透明的模式
    SDL_SetTextureBlendMode(blackTexture, SDL_BLENDMODE_BLEND); // 把blackTexture设置成可以支持半透明的模
    SDL_SetTextureAlphaMod(blackTexture, 25);

    SDL_Rect catPosition;     // 猫的位置，大小
    SDL_Rect blackRect; // 黑色背景的位置，大小

    catPosition.x = 0;
    catPosition.y = 0;
    catPosition.w = catSurface->w / 5;
    catPosition.h = catSurface->h / 5;

    blackRect.x = 0;
    blackRect.y = 0;
    blackRect.h = windowSurface->h;
    blackRect.w = windowSurface->w;

    printf("SDL Is Loading Music...\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // 音频输出设置
    Mix_Music* sound = Mix_LoadMUS("Lemon.wav");   // 加载音频


    printf("SDL Strat To Play Music.\n");

    Mix_PlayMusic(sound, 100);  // 播放音频

    /*事件循环*/
    bool quit = false;
    SDL_Event event;

    while(!quit)    // quit为真退出循环
    {

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(event.type == SDL_MOUSEMOTION)
            {
                catPosition.x = event.motion.x - catSurface->w / 10;
                catPosition.y = event.motion.y - catSurface->h / 10;
                printf("(%4d, %3d)\n", catPosition.x, catPosition.y);
            }
        }

        SDL_RenderCopy(pRend, blackTexture, NULL, &blackRect);
        SDL_RenderCopy(pRend, catTexture, NULL, &catPosition); // 显示图片

        //printf("alpha = %d\n", alpha);

        SDL_Delay(10);
        SDL_RenderPresent(pRend);   // 显示Texture
    }

    printf("SDL Quit.");

    return 0;
}
