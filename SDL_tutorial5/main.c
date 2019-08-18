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

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);   // ��ʼ��

    printf("SDL Create Window...\n");

    /* �������� */
    SDL_Window* window = SDL_CreateWindow("Main",      // ����
                                           WINDOW_X, WINDOW_Y,    // ���Ͻǵ�λ��
                                           WINDOW_WIDTH, WINDOW_HEIGHT,    // ��С
                                           SDL_WINDOW_SHOWN);   // ģʽ
    SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    printf("SDL Create Renderer...\n");


    SDL_Renderer* pRend = SDL_CreateRenderer(window, // ��Ⱦ�Ĵ���
                                             -1,
                                             SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND); // ������Ⱦģʽ

    SDL_RenderClear(pRend); // ����

    printf("SDL Is Loading Picture...\n");
    SDL_Surface* tigerSurface = IMG_Load("tiger3.jpg");     // ����ͼƬ
    SDL_SetColorKey(tigerSurface, SDL_TRUE, SDL_MapRGB(tigerSurface->format, 255, 255, 255));
    SDL_Texture* tigerTexture = SDL_CreateTextureFromSurface(pRend, tigerSurface);  // ����tiger��Texture

    int i;  // ͼƬ�±�
    int tigerWidth = tigerSurface->w / 13;  // ͼƬ�Ŀ��
    int tigerHeight = tigerSurface->h;  // ͼƬ�ĸ߶�
    SDL_Rect tigerPosition;     // ͼƬ��λ�ã���С
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

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // ��Ƶ�������
    Mix_Music* sound = Mix_LoadMUS("Lemon.wav");   // ������Ƶ


    printf("SDL Strat To Play Music.\n");

    Mix_PlayMusic(sound, 100);  // ������Ƶ

    /*�¼�ѭ��*/
    bool quit = false;
    SDL_Event event;

    while(!quit)    // quitΪ���˳�ѭ��
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

        SDL_RenderClear(pRend);     // ���Renderer
        SDL_RenderCopy(pRend,   // Դ
                       tigerTexture,    // Ŀ��
                        &chips[i],    //
                       &tigerPosition); // ͼƬ��λ�ã�����ѹ����
        printf("i = %d\n", i);

        SDL_Delay(100);
        SDL_RenderPresent(pRend);   // ��ʾTexture
    }

    printf("SDL Quit.");

    return 0;
}
