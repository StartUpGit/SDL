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
    SDL_Window* window = SDL_CreateWindow("Main",      // 标题
                                           WINDOW_X, WINDOW_Y,    // 右上角的位置
                                           WINDOW_WIDTH, WINDOW_HEIGHT,    // 大小
                                           SDL_WINDOW_SHOWN);   // 模式
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    printf("SDL Create Renderer...\n");


    SDL_Renderer* pRend = SDL_CreateRenderer(window, // 渲染的窗口
                                             -1,
                                             SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND); // 设置渲染模式

    SDL_RenderClear(pRend); // 清屏

    printf("SDL Is Loading Picture...\n");
    SDL_Surface* tigerSurface = IMG_Load("tiger3.jpg");     // 加载图片
    SDL_SetColorKey(tigerSurface, SDL_TRUE, SDL_MapRGB(tigerSurface->format, 255, 255, 255));
    SDL_Texture* tigerTexture = SDL_CreateTextureFromSurface(pRend, tigerSurface);  // 创建tiger的Texture

    int i;  // 图片下标
    int tigerWidth = tigerSurface->w / 13;  // 图片的宽度
    int tigerHeight = tigerSurface->h;  // 图片的高度
    SDL_Rect tigerPosition;     // 图片的位置，大小
    tigerPosition.x = windowSurface->w / 2 - tigerSurface->w / 26;
    tigerPosition.y = 0;
    tigerPosition.w = tigerSurface->w / 13;
    tigerPosition.h = tigerSurface->h;

    SDL_Rect chips[13];
    for(i = 0; i < 13; i++)
    {
        chips[i].x = tigerWidth * i;
        chips[i].y = 0;
        chips[i].w = tigerWidth;
        chips[i].h = tigerHeight;
    }
    i = 0;

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
        }

        i = (i + 1) % 6;
        if(tigerPosition.x <= -tigerWidth)
        {
            tigerPosition.x = windowSurface->w;
        }

        SDL_RenderClear(pRend);     // 清空Renderer
        SDL_RenderCopy(pRend,   // 源
                       tigerTexture,    // 目标
                        &chips[i],    //
                       &tigerPosition); // 图片的位置，拉伸压缩比
        printf("i = %d\n", i);

        SDL_Delay(100);
        SDL_RenderPresent(pRend);   // 显示Texture
    }

    printf("SDL Quit.");

    return 0;
}
