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


    SDL_Renderer* pRend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND);

    SDL_RenderClear(pRend); // ����

    bool quit = false;
    SDL_Event event;

    printf("SDL Is Loading Picture...\n");
    SDL_Surface* fireworkImgSurface = IMG_Load("firework.bmp");     // ����ͼƬ
    SDL_BlitSurface(fireworkImgSurface, NULL, windowSurface, NULL);     // ��ͼƬ������Ļ��
    SDL_UpdateWindowSurface(window);    // ������Ļ

    printf("SDL Is Loading Music...\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // ��Ƶ�������
    Mix_Music* sound = Mix_LoadMUS("Lemon.wav");   // ������Ƶ


    printf("SDL Strat To Play Music.\n");

    Mix_PlayMusic(sound, 100);  // ������Ƶ

    /*�¼�ѭ��*/
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_Delay(5);
        SDL_RenderPresent(pRend);
    }

    printf("SDL Quit.");

    return 0;
}
