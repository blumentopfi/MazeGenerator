#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Bitmap.h"
#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define RED   0x00FF0000
#define GREEN 0x0000FF00
#define BLUE  0x000000FF
#define YELLOW 0x00FFF700
#define turk   0x0000FFFF



void generateMaze(uint32_t *data){
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

void solveMaze (int x,int y,uint32_t *data){
    if ( FindPathToExit( x, y, data ) == 0 ) {
        printf("Kein Ausgang vorhanden");
    } else {
        printf("Found Exit and marked it");
    }
}

int FindPathToExit (int x,int y,uint32_t *data){
       UpdateScreen(data,0) ;
       if (x < 0 || x >= BMP_WIDTH || y < 0 || y >= BMP_HEIGHT ){
        return 0;
       }

       if (data[(y)*BMP_WIDTH+x]==GREEN){
        setPixel(x,y,RED,data);
        return 1;
       }




       if (data[(y)*BMP_WIDTH+x]==BLACK || data[(y)*BMP_WIDTH+x]==RED || data[(y)*BMP_WIDTH+x]==turk){
        return 0;
       }

       setPixel(x,y,RED,data);

       if(FindPathToExit(x+1,y,data)==1) return 1;
       if(FindPathToExit(x-1,y,data)==1) return 1;
       if(FindPathToExit(x,y+1,data)==1) return 1;
       if(FindPathToExit(x,y-1,data)==1) return 1;

       setPixel(x,y,turk,data);

       return 0;
}



void rectangle (uint32_t *data) {
    int a,b;
    for (a=0;a<=BMP_HEIGHT-1;a++){
        for(b=0;b<=BMP_WIDTH-1;b++){

                setPixel(a, b, BLACK, data);

        }
    }
}









/**
 * Hauptprogramm
 */
int main(int argc, char* args[]) {

   int x, y, a=0,b=0 ;

    uint32_t *data = NULL;
    printf("Bitte ungerade Zahl eingeben: \n ");
    scanf("%d",&BMP_HEIGHT);
    BMP_WIDTH = BMP_HEIGHT;
    InitializeWindow();

    data = (uint32_t*)malloc ( BMP_WIDTH*BMP_HEIGHT*sizeof(uint32_t));
    rectangle(data);
    generateMaze(data);

     do {
        a = rand()%BMP_HEIGHT-1;
        b= a;
     }while(a %2 == 0 );

    printf("A: %d,B: %d",a,b);
    solveMaze(a,b,data);
    setPixel(a,b,YELLOW,data);
    SaveBitmapAsFile(data,"raster");

    free(data);

    return 0;
}




