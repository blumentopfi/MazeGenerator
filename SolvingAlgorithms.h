
#ifndef __Solving_h__
#define __Solving_h__
#include <stdio.h>
#include "Graphics.h"
#include "Bitmap.h"



void WorstSolvingAlgorithm(int x,int y,uint32_t *data){
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
#endif
