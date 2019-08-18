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
    //SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    printf("SDL Create Renderer...\n");
    SDL_Renderer* pRend = SDL_CreateRenderer(window, // 渲染的窗口
                                             -1,
                                             SDL_RENDERER_ACCELERATED); //
    SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(pRend); // 清屏



    printf("SDL Is Loading Picture...\n");
    SDL_Surface* qie = IMG_Load("qie3.jpg");     // 加载图片
    SDL_Texture* qieTexture = SDL_CreateTextureFromSurface(pRend, qie); // 创建图片的Texture

    printf("SDL Is Loading Music...\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // 音频输出设置
    Mix_Music* sound = Mix_LoadMUS("Lemon.wav");   // 加载音频


    printf("SDL Strat To Play Music.\n");

    Mix_PlayMusic(sound, 100);  // 播放音频

    // 图片坐标
    SDL_Rect piePlace;
    piePlace.x = 0;
    piePlace.y = 0;
    piePlace.h = qie->h;
    piePlace.w = qie->w;

    /*事件循环*/
    bool quit = false;
    SDL_Event event;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
            else if(event.type == SDL_MOUSEMOTION)  // 鼠标移动
            {
                printf("Mouse Coordinates:");
                piePlace.x = event.motion.x - qie->w / 2;
                piePlace.y = event.motion.y - qie->h / 2;
                printf("(%.3d, %.3d)\n", piePlace.x, piePlace.y);


            }
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    printf("Left Key\n");
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    printf("Right Key\n");
                }
                else
                {
                    ;
                }
            }
        }

        SDL_RenderClear(pRend);
        SDL_RenderCopy(pRend,   // 目标Texture
                       qieTexture,  // 源Texture
                       NULL,
                       &piePlace);   // 贴图的位置


        SDL_Delay(5);
        SDL_RenderPresent(pRend);   // 显示Texture
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("SDL Quit.");

    return 0;
}
