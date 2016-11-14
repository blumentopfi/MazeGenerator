#ifndef __graphics_h__
#define __graphics_h__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
int BMP_HEIGHT = 333;
int BMP_WIDTH = 333;
int BytemapCounter = 0 ;
SDL_Window* m_window = NULL ;
SDL_Surface* ScreenSurface = NULL ;
SDL_Surface* image = NULL;

int InitializeWindow(){
if (SDL_Init(SDL_INIT_VIDEO) < 0){
    printf("Init failed Error: %s \n",SDL_GetError()) ;
} else {
    m_window = SDL_CreateWindow("Maze",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,BMP_HEIGHT,BMP_WIDTH,SDL_WINDOW_SHOWN);
    //SDL_SetWindowFullscreen(m_window,SDL_WINDOW_FULLSCREEN);
    if (m_window == NULL){
        printf("Windows failed Error: %s",SDL_GetError()) ;
    }else{
    ScreenSurface = SDL_GetWindowSurface(m_window);
    }

}
}

int UpdateScreen(uint32_t *data,int FPS){
    image = SDL_CreateRGBSurfaceFrom(data,BMP_WIDTH,BMP_HEIGHT,32,4*BMP_WIDTH,0,0,0,0);
    SDL_BlitSurface(image,NULL,ScreenSurface,NULL) ;
    SDL_UpdateWindowSurface(m_window);
    SDL_FreeSurface(image);
    SDL_Delay(FPS);
}



#endif
