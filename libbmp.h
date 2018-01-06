#ifndef LIBBMP
#define LIBBMP

//only 24-bit bitmap file supported.
#include "vardef.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

class Bmp
{
    public:
        int height, width;//image size.
        
        //must have bmp info data.
        // Bmp();
        Bmp(int theight=100, int twidth=100);
        Bmp(BmpFileHeader fileh, BmpInfoHeader infoh);
        void resize(int theight=100, int twidth=100);
        void save(const char* filename="save.bmp");
        bool setPixel(int x, int y, rgbTriple color);
        bool setNormalPixel(int x, int y, rgbTriple color);
        bool read(const char* filename="read.bmp");

        
    private:
        tagRGBTRIPLE **datas;
        BmpFileHeader fileHeader;
        BmpInfoHeader infoHeader;
        int padBytes;


        void init();//init some general things.
        void memory();
        
};

#endif
