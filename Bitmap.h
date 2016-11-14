
#ifndef __Bitmap_h__
#define __Bitmap_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void SaveBitmapAsFile(uint32_t *data,char* Filename){
    int y , x  ;

    FILE *file = fopen(strcat(Filename,".bmp"), "w");
    bitmap_file_header(file);
    bitmap_info_header(file);
    for (y = 0; y < BMP_HEIGHT; y++) {
        for (x = 0; x < BMP_WIDTH; x++) {
            write_N_byte(file, data[y * BMP_WIDTH + x], 4);
        }
    }
    fclose(file);
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
        fputc(byte % 256,file) ;
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


#endif
