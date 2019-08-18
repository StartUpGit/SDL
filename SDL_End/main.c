
/* Include -------------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "main.h"

/* global ---------------------------------------------------------------------------- */

/* function -------------------------------------------------------------------------- */
void Init(void);    // 初始化
void CreateWindow(void);    //创建窗口
void LoadAsset(void); // 加载素材
void EventLoop(void);   // 事件循环

SDL_Rect RectConversion(SDL_Rect CenterRe3333333ct);    // 坐标转换

/* Variable -------------------------------------------------------------------------- */
// 窗口相关
SDL_Window* window = NULL;          // SDL窗口
SDL_Surface* windowSurface = NULL;  // SDL窗口的Surface
SDL_Renderer* pRenderer = NULL;     // SDL窗口的渲染器

// 上升中的烟花
SDL_Surface* pRisingFireworkSurface = NULL;
SDL_Texture* pRisingFireworkTexture = NULL;

// 开始爆炸的烟花
SDL_Surface* pExplodingFireworkSurface = NULL;
SDL_Texture* pExplodingFireworkTexture = NULL;

// 炸开的烟花
SDL_Surface* pExplodedFireworkSurface = NULL;
SDL_Texture* pExplodedFireworkTexture = NULL;

// 黑色背景
SDL_Surface* pBlackBackgroundSurface = NULL;
SDL_Texture* pBlackBackgroundTexture = NULL;

// 背景音乐
Mix_Music* pStarSky = NULL;

/* main ------------------------------------------------------------------------------ */
int main(int argc, char* argv[])
{
    Init();

    CreateWindow();

    LoadAsset();

    Mix_PlayMusic(pStarSky, 100);  // 播放音频

    EventLoop();

    printf("SDL Quit.");

    return 0;
}


// SDL及其组件初始化
// 初始化SDL基本插件 SDL_Mixer, SDL_image, SDL_ttf
void Init(void)
{
    printf("SDL Init...\n");

    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("Init SDL Failed!\n");
        printf("Init Error: %s \n", SDL_GetError());
    }

    if(Mix_Init(MIX_INIT_FLAC) != MIX_INIT_FLAC)
    {
        printf("Init SDL mixer failed!\n");
        printf("Init Error: %s \n", SDL_GetError());
    }

    //printf("%d \n", IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF));

    if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        printf("Init SDL image failed!\n");
        printf("Init Error: %s \n", SDL_GetError());
    }

    if(TTF_Init() == -1)
    {
        printf("Init SDL ttf failed!\n");
        printf("Init Error: %s \n", SDL_GetError());
    }
}


// 创建窗口及其渲染器
// 设置渲染模式为SDL_BLENDMODE_BLEND
// 清屏
void CreateWindow(void)
{
    printf("SDL Create Window...\n");

    /* 创建窗口 */
    window = SDL_CreateWindow("Main", WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    windowSurface = SDL_GetWindowSurface(window);

    printf("SDL Create Renderer...\n");

    pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND); // 设置渲染模式

    SDL_RenderClear(pRenderer); // 清屏

}


// 加载资源
void LoadAsset(void)
{
    printf("Loading Asset...\n");

    // 加载上升中的烟花
    pRisingFireworkSurface = IMG_Load("./asset/firework6.png"); // 加载上升中的烟花
    if(pRisingFireworkSurface == NULL)
    {
        printf("Load file: ./asset/firework6.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }
    pRisingFireworkTexture = SDL_CreateTextureFromSurface(pRenderer, pRisingFireworkSurface);   // 创建升起烟花的纹理
    if(pRisingFireworkTexture == NULL)
    {
        printf("Load file ./asset/firework6.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }

    // 开始爆炸的烟花
    pExplodingFireworkSurface = IMG_Load("./asset/firework10.png");  // 加载爆炸中的烟花
    if(pExplodingFireworkSurface == NULL)
    {
        printf("Load file: ./asset/firework5.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }
    pExplodingFireworkTexture = SDL_CreateTextureFromSurface(pRenderer, pExplodingFireworkSurface); // 创建爆炸中烟花的纹理
    if(pExplodingFireworkTexture == NULL)
    {
        printf("Load file: ./asset/firework5.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }

    // 炸开的烟花
    pExplodedFireworkSurface = IMG_Load("./asset/firework7.png");  // 加载爆炸中的烟花
    if(pExplodedFireworkSurface == NULL)
    {
        printf("Load file: ./asset/firework7.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }
    pExplodedFireworkTexture = SDL_CreateTextureFromSurface(pRenderer, pExplodedFireworkSurface); // 创建爆炸中烟花的纹理
    if(pExplodedFireworkTexture == NULL)
    {
        printf("Load file: ./asset/firework7.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }

    // 黑色背景
    pBlackBackgroundSurface = IMG_Load("./asset/background.png");  // 加载爆炸中的烟花
    if(pBlackBackgroundSurface == NULL)
    {
        printf("Load file: ./asset/background.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }
    pBlackBackgroundTexture = SDL_CreateTextureFromSurface(pRenderer, pBlackBackgroundSurface); // 创建爆炸中烟花的纹理
    if(pBlackBackgroundTexture == NULL)
    {
        printf("Load file: ./asset/background.png failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }


    // 加载背景音乐
    printf("Loading music...\n");

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);    // 音频输出设置
    pStarSky = Mix_LoadMUS("./asset/StarSky.flac");
    if(pStarSky == NULL)
    {
        printf("Load file: ./asset/StarSky.flac failed!\n");
        printf("Loading Error:%s \n", SDL_GetError());
    }
}



void EventLoop(void)
{
    printf("Event loop...\n");

    SDL_Rect backgroundPosition;
    backgroundPosition.x = 0;
    backgroundPosition.y = 0;
    backgroundPosition.w = WINDOW_WIDTH;
    backgroundPosition.h = WINDOW_HEIGHT;

    SDL_Rect fireworkPosition;
    fireworkPosition.x = 0;
    fireworkPosition.y = 0;
    fireworkPosition.h = 0;
    fireworkPosition.w = 0;

    SDL_Rect fireworkCenterPosition;
    fireworkCenterPosition.x = WINDOW_WIDTH / 2;
    fireworkCenterPosition.y = 480;
    fireworkCenterPosition.w = 50;
    fireworkCenterPosition.h = 50;

    SDL_Event event;    // 事件
    bool quit = false;  // 退出标志
    int step = 0;   // 标志延缓绽放到哪一步

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_RenderCopy(pRenderer, pBlackBackgroundTexture, NULL, &backgroundPosition);

        if(step == 0)   // 烟花上升过程
        {

            //printf("> %d >\n", fireworkCenterPosition.y);

            fireworkCenterPosition.y -= 2;  // 位置升高

            fireworkPosition = RectConversion(fireworkCenterPosition);  // 坐标转换

            SDL_RenderCopy(pRenderer, pRisingFireworkTexture, NULL, &fireworkPosition);

            if(fireworkCenterPosition.y <= WINDOW_HEIGHT / 3)
            {
                //printf("< %d >\n", fireworkCenterPosition.w);

                step = 1;

                fireworkCenterPosition.x = WINDOW_WIDTH / 2;
                fireworkCenterPosition.y = WINDOW_HEIGHT / 3;
                fireworkCenterPosition.w = 50;
                fireworkCenterPosition.h = 50;
            }
        }
//        else if(step == 1)
//        {
//            step = 2;
//            fireworkCenterPosition.x = WINDOW_WIDTH / 2;
//            fireworkCenterPosition.y = WINDOW_HEIGHT / 3;
//            fireworkCenterPosition.w = 10;
//            fireworkCenterPosition.h = 10;
//        }
        else if(step == 1)
        {
            fireworkCenterPosition.h += 2;  // 烟花面积变大
            fireworkCenterPosition.w += 2;

            fireworkPosition = RectConversion(fireworkCenterPosition);
            // 复制图片到渲染器
            SDL_RenderCopy(pRenderer, pExplodingFireworkTexture, NULL, &fireworkPosition);

            // 当烟花面积到达最大
            if((fireworkCenterPosition.h >= WINDOW_HEIGHT / 2) || (fireworkCenterPosition.w >= WINDOW_WIDTH / 2))
            {
                step = 0;
                fireworkCenterPosition.x = WINDOW_WIDTH / 2;
                fireworkCenterPosition.y = WINDOW_HEIGHT;
                fireworkCenterPosition.w = 50;
                fireworkCenterPosition.h = 50;
            }

        }
        else
        {

        }

        SDL_RenderPresent(pRenderer);
        SDL_Delay(5);

        SDL_RenderClear(pRenderer); // 清屏
    }
}


// 将图片中心坐标转化为图片右上角坐标
// 方便显示
SDL_Rect RectConversion(SDL_Rect CenterRect)
{
    SDL_Rect rect;

    rect.x = CenterRect.x - CenterRect.w / 2;
    rect.y = CenterRect.y - CenterRect.h / 2;
    rect.w = CenterRect.w;
    rect.h = CenterRect.h;

    return rect;
}



















