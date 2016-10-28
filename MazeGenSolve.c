#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int BMP_HEIGHT = 633;
int BMP_WIDTH = 633;

#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define RED   0x00FF0000
#define GREEN 0x0000FF00
#define BLUE  0x000000FF
#define YELLOW 0x00FFF700
#define turk   0x0000FFFF


struct Cell {
    int y;
    int x;
    int VorCellX;
    int VorCellY;
};

/**
 * Schreibt die N letzten Bytes eines 64-bit Integers in einen File-Deskriptor.
 * Das am wenigsten signifikante Byte (LSB) wird zuerst geschrieben.
 * (Little Endian).
 *
 * Eingabeparameter:
 *   file: File-Deskriptor.
 *   byte: Byte-Muster.
 *   N: Anzahl der zu schreibenden Bytes (N <= 8).
 */
void write_N_byte(FILE * file, uint64_t byte, int N) {
    int i;
    for(i = 0; i < N; i++) {
        fputc(byte % 256, file);
        byte /= 256;
    }
}

/**
 * Im BMP zugeordneten Daten-Array "data" wird an der Koordinate (x,y) der
 * Pixel auf den Wert "color" gesetzt.
 *
 * Eingabeparameter:
 *   x: X-Koordinate im BMP.s
 *   y: Y-Koordinate im BMP.
 *   color: Pixelfarbe.
 *   data: BMP Daten-Array.
 */
void setPixel(int x, int y, uint32_t color, uint32_t * data) {
    data[y*BMP_WIDTH+x] = color;
}

/**
 * Erstellt einen BMP-File-Header, insgesamt 14 Byte.
 *
 * Eingabeparameter:
 *   file: File-Deskriptor, der geoeffneten BMP-Datei.
 */
void bitmap_file_header(FILE * file) {
    // (2 Byte, uint16_t) ASCII-Zeichenkette "BM" (Hex: 0x42 0x4D Dez: 19778).
    write_N_byte(file, 'B', 1);
    write_N_byte(file, 'M', 1);
    // (4 Byte, uint32_t) Groesse der BMP-Datei in Byte.
    // = bitmap_file_header + bitmap_info_header + Daten
    write_N_byte(file, 14 + 40 + BMP_WIDTH * BMP_HEIGHT * 32, 4);
    // (4 Byte, uint32_t) Reserviert, Standard: 0
    write_N_byte(file, 0, 4);
    // (4 Byte, uint32_t) Offset der Bilddaten in Byte vom Beginn der Datei an,
    // bei Echtfarben fast immer 54 (manche Software ignoriert diese Angabe
    // daher fehlerhafterweise).
    write_N_byte(file, 54, 4);
}

void mypause ( void )
{
    printf ( "Press [Enter] to continue . . ." );
    fflush ( stdout );
    getchar();
}

void generateMaze2(uint32_t *data){
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

/**
 * Erstellt einen BMP-Info-Header, insgesamt 40 Byte.
 *
 * Eingabeparameter:
 *   file: File-Deskriptor, der geoeffneten BMP-Datei.
 */
void bitmap_info_header(FILE * file) {
  // (4 Byte, uint32_t) Groesse von bitmap_info_header in Byte
  write_N_byte(file, 40, 4);
  // (4 Byte, int32_t) Breite der Bitmap in Pixel.
  write_N_byte(file, BMP_WIDTH, 4);
  // (4 Byte, int32_t) Hoehe der Bitmap in Pixel. Negativ: top-bottom.
  write_N_byte(file, -BMP_HEIGHT, 4);
  // (2 Byte, uint16_t) Anzahl der Farbebenen, nicht fuer BMP verwendet
  write_N_byte(file, 1, 2);
  // (2 Byte, uint16_t) Gibt die Farbtiefe der Bitmap in bpp an; muss einer
  // der folgenden Werte sein: 1, 4, 8, 16, 24 oder 32. Bei 1, 4 und 8 bpp
  // sind die Farben indiziert.
  write_N_byte(file, 32, 2);
  // (4 Byte, uint32_t) Keine Kompression verwendet = 0
  write_N_byte(file, 0, 4);
  // (4 Byte, uint32_t) Groesse der reinen Bilddaten in Byte (mit padding).
  write_N_byte(file, BMP_WIDTH * BMP_HEIGHT * 32, 4);
  // (4 Byte, int32_t) Horizontale Aufloesung des Zielausgabegerätes in Pixel
  // pro Meter; wird aber fuer BMP-Dateien meistens auf 0 gesetzt.
  write_N_byte(file, 0, 4);
  // (4 Byte, int32_t) Vertikale Aufloesung des Zielausgabegerätes in Pixel
  // pro Meter; wird aber fuer BMP-Dateien meistens auf 0 gesetzt.
  write_N_byte(file, 0, 4);
  // (4 Byte, uint32_t) Anzahl der Eintraege der Farbtabelle; 0 bedeutet keine.
  write_N_byte(file, 0, 4);
  // (4 Byte, uint32_t) Anzahl wichtiger Farben; 0 bedeutet alle sind wichtig.
  write_N_byte(file, 0, 4);
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
int main() {

    int x, y, a=0,b=0 ;

    printf("Bitte ungerade Zahl eingeben: \n ");
    scanf("%d",&BMP_HEIGHT);
    BMP_WIDTH = BMP_HEIGHT;
    uint32_t *data = NULL;
    data = (uint32_t*)malloc ( BMP_WIDTH*BMP_HEIGHT*sizeof(uint32_t));
    printf("%d\n", BMP_WIDTH*BMP_HEIGHT*sizeof(uint32_t));
    rectangle(data);
    generateMaze2(data);

 do {
    a = rand()%BMP_HEIGHT-1;
    b= a;
 }while(a %2 == 0 );

    printf("A: %d,B: %d",a,b);
    solveMaze(a,b,data);
    setPixel(a,b,YELLOW,data);
    // Schreibe BMP Datei
    FILE *file = fopen("raster.bmp", "w");
    bitmap_file_header(file);
    bitmap_info_header(file);
    for (y = 0; y < BMP_HEIGHT; y++) {
        for (x = 0; x < BMP_WIDTH; x++) {
            write_N_byte(file, data[y * BMP_WIDTH + x], 4);
        }
    }
    fclose(file);
    //free(data);

    return 0;
}
