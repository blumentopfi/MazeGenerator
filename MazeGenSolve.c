#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "Graphics.h"
#include "Bitmap.h"
#include "GenerationAlgorithms.h"
#include "SolvingAlgorithms.h"





/**
 * Hauptprogramm
 */
int main(int argc, char* args[]) {

   int x, y, a=0,b=0 ;
    char Filename[25] ;
    uint32_t *data = NULL;
    printf("Bitte ungerade Zahl eingeben: \n ");
    scanf("%d",&BMP_HEIGHT);
    BMP_WIDTH = BMP_HEIGHT;
     printf("Bitte Dateinamen zum speichern eingeben") ;
    scanf("%s",&Filename);
    InitializeWindow();

    data = malloc ( BMP_WIDTH*BMP_HEIGHT*sizeof(uint32_t));

    InitializeBMPWithBlackBackground(data);

    recursiveBacktracing(data);

     do {
        a = rand()%BMP_HEIGHT-1;
        b= a;
     }while(a %2 == 0 );

    WorstSolvingAlgorithm(a,b,data);

    setPixel(a,b,YELLOW,data);

    SaveBitmapAsFile(data,Filename);



    free(data);

    SDL_Delay(10000);

    return 0;
}




