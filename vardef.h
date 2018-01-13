#ifndef VARDEF
#define VARDEF
// #ifndef _WINDOWS_H
#pragma pack(push)
#pragma pack(1)//to avoid memory alignment.
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef long LONG;


struct mytagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

struct mytagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
};


struct mytagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};
#pragma pack(pop)
// #endif

typedef mytagBITMAPFILEHEADER BmpFileHeader;
typedef mytagBITMAPINFOHEADER BmpInfoHeader;
typedef mytagRGBTRIPLE rgbTriple;


#endif
