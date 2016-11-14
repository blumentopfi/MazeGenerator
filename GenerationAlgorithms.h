#ifndef __generation_h__
#define __generation_h__

#include <stdio.h>
#include <stdlib.h>
#include "Graphics.h"
#include "Bitmap.h"


void recursiveBacktracing(uint32_t *data){
    int Startx,Starty,counter,oldx,oldy;
    srand(time(NULL));

    while (Startx % 2 ==0 || Starty %2 ==0){
        Startx = (rand() % BMP_WIDTH-1)+1;
        Starty = (rand() % BMP_HEIGHT-1)+1;
    }

    setPixel(Startx, Starty, WHITE, data);
    recursion(Startx, Starty, data);
    generateExit(data);
}

void recursion (int x,int y,uint32_t *data) {
    UpdateScreen(data,0);
    int dir[4];
    int i;
    fillIntWithRanDir(dir);

    for( i = 0; i < 4; i++ ) {
        switch( dir[i] ){
        case 0:
            if( x-2 <= 0 ) {
                continue;
            }
            if (data[y*BMP_WIDTH+x-2] != WHITE){
                setPixel(x-2,y,WHITE,data);
                setPixel(x-1,y,WHITE,data);
                recursion(x-2,y,data);
            }
            break;
        case 1:
            if( y + 2 >= BMP_HEIGHT - 1 ){
                continue;
            }
            if (data[(y+2)*BMP_WIDTH+x] != WHITE){
                setPixel(x,y+2,WHITE,data);
                setPixel(x,y+1,WHITE,data);
                recursion(x,y+2,data);
            }
            break;
        case 2:
            if( x + 2 >= BMP_WIDTH ){
                continue;
            }
            if ( data[y*BMP_WIDTH+x+2] != WHITE ){
                setPixel(x+2,y,WHITE,data);
                setPixel(x+1,y,WHITE,data);
                recursion(x+2,y,data);
            }
            break;
        case 3:
            if( y - 2 <= 0 ){
                continue;
            }
            if (data[(y-2)*BMP_WIDTH+x] != WHITE){
                setPixel(x,y-2,WHITE,data);
                setPixel(x,y-1,WHITE,data);
                recursion(x,y-2,data);
            }
            break;
        }
    }
}

 void shuffle(int *array, size_t n)
{
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void generateExit (uint32_t *data){
   int  random;
   int  random2;
   int  y = 0;
   int  x = 0;

   random = rand()%4;

   switch( random ) {
    case 0:
        while(data[(y+1)*BMP_WIDTH+random2]!=WHITE){
            random2 = rand() % BMP_WIDTH-1;
        }
        setPixel(random2,y,GREEN,data);
        break;
    case 1:
        while(data[(random2)*BMP_WIDTH+x+1]!=WHITE){
            random2 = rand() % BMP_HEIGHT-1;
        }
        setPixel(x,random2,GREEN,data);
        break;
    case 2:
        while(data[(random2)*BMP_WIDTH+x+1]!=WHITE){
            random2 = rand() % BMP_HEIGHT-1;
        }
        setPixel(BMP_WIDTH-1,random2,GREEN,data);
        break;
    case 3:
        while(data[(random2)*BMP_WIDTH+x+1]!=WHITE){
            random2 = rand() % BMP_WIDTH-1;
        }
        setPixel(random2,BMP_HEIGHT-1,GREEN,data);
        break;
    }
}

void fillIntWithRanDir( int *dir ) {
    int i;
    for( i = 0; i < 4; i++ ) {
        dir[i] = i;
    }
    shuffle( dir, 4 );
}
#endif
