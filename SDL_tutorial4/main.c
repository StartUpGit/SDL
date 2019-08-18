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
    //SDL_Surface* windowSurface = SDL_GetWindowSurface(window);

    printf("SDL Create Renderer...\n");
    SDL_Renderer* pRend = SDL_CreateRenderer(window, // ��Ⱦ�Ĵ���
                                             -1,
                                             SDL_RENDERER_ACCELERATED); //
    SDL_SetRenderDrawBlendMode(pRend, SDL_BLENDMODE_BLEND);
    SDL_RenderClear(pRend); // ����



    printf("SDL Is Loading Picture...\n");
    SDL_Surface* qie = IMG_Load("qie3.jpg");     // ����ͼƬ
    SDL_Texture* qieTexture = SDL_CreateTextureFromSurface(pRend, qie); // ����ͼƬ��Texture

    printf("SDL Is Loading Music...\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // ��Ƶ�������
    Mix_Music* sound = Mix_LoadMUS("Lemon.wav");   // ������Ƶ


    printf("SDL Strat To Play Music.\n");

    Mix_PlayMusic(sound, 100);  // ������Ƶ

    // ͼƬ����
    SDL_Rect piePlace;
    piePlace.x = 0;
    piePlace.y = 0;
    piePlace.h = qie->h;
    piePlace.w = qie->w;

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
            else if(event.type == SDL_MOUSEMOTION)  // ����ƶ�
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
        SDL_RenderCopy(pRend,   // Ŀ��Texture
                       qieTexture,  // ԴTexture
                       NULL,
                       &piePlace);   // ��ͼ��λ��


        SDL_Delay(5);
        SDL_RenderPresent(pRend);   // ��ʾTexture
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    printf("SDL Quit.");

    return 0;
}
