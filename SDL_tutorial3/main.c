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


    //SDL_Renderer* pRend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND);

    //SDL_RenderClear(pRend); // ����


    SDL_Rect emojPlace;
    emojPlace.x = 0;
    emojPlace.y = 0;

    printf("SDL Is Loading Picture...\n");
    SDL_Surface* emoj1 = IMG_Load("emoj1.jpg");     // ����ͼƬ1
    SDL_Surface* emoj2 = IMG_Load("emoj2.jpg");     // ����ͼƬ2
    SDL_Surface* emoj = emoj1;

    printf("SDL Is Loading Music...\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // ��Ƶ�������
    Mix_Music* sound = Mix_LoadMUS("Lemon.wav");   // ������Ƶ


    printf("SDL Strat To Play Music.\n");

    Mix_PlayMusic(sound, 100);  // ������Ƶ

    /*�¼�ѭ��*/
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
            else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    printf("Left\n");
                    emoj = emoj1;
                }
                else if(event.button.button == SDL_BUTTON_RIGHT)
                {
                    printf("Right\n");
                    emoj = emoj2;
                }
                else
                {
                    ;
                }
            }
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_w)
                {
                    emojPlace.y -= 10;
                    printf("w\n");
                }
                else if(event.key.keysym.sym == SDLK_a)
                {
                    emojPlace.x -= 10;
                    printf("a\n");
                }
                else if(event.key.keysym.sym == SDLK_s)
                {
                    emojPlace.y += 10;
                    if(emojPlace.y > 685)
                    {
                        emojPlace.y = 685;
                    }
                    printf("s\n");
                }
                else if(event.key.keysym.sym == SDLK_d)
                {
                    emojPlace.x += 10;
                    if(emojPlace.x > 845)
                    {
                        emojPlace.x = 845;
                    }
                    printf("d\n");
                    }
                }

            SDL_FillRect(windowSurface, NULL, 0);
            SDL_BlitSurface(emoj, NULL, windowSurface, &emojPlace);
            SDL_UpdateWindowSurface(window);

        }

        SDL_Delay(5);
        //SDL_RenderPresent(pRend);
    }

    printf("SDL Quit.");

    return 0;
}
