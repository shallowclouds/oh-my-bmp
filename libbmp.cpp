#include "libbmp.h"

void Bmp::memory()
{
    datas=(rgbTriple**)malloc(sizeof(rgbTriple*)*height);
    for(int i=0; i<height; i++)
    {
        datas[i]=(rgbTriple*)malloc(sizeof(rgbTriple)*width);
        memset(datas[i], 0, sizeof(rgbTriple)*width);
    }
}

void Bmp::init()
{
    memset(&(this->fileHeader), 0, sizeof(this->fileHeader));
    memset(&(this->infoHeader), 0, sizeof(this->infoHeader));
    int tmpBytes=width*sizeof(rgbTriple);
    if(tmpBytes%4!=0)
    {
        this->padBytes=(tmpBytes/4+1)*4-tmpBytes;
    }
    else
        this->padBytes=0;
    int bsize=sizeof(BmpFileHeader)+sizeof(BmpInfoHeader)+(height*width)*sizeof(rgbTriple)+padBytes*height;


    this->fileHeader=(BmpFileHeader){0x4d42, bsize, 0, 0, (sizeof(BmpFileHeader)+sizeof(BmpInfoHeader))};
    this->infoHeader=(BmpInfoHeader){sizeof(BmpInfoHeader), this->width, this->height, 1, 24, 0, height*width*sizeof(rgbTriple)+padBytes*height, 0, 0, 0, 0};
    this->memory();
}

// Bmp::Bmp()
// {
//     this->init();
// }

Bmp::Bmp(int theight, int twidth)
:height(theight), width(twidth)
{
    this->init();
}

Bmp::Bmp(BmpFileHeader fileh, BmpInfoHeader infoh)
:fileHeader(fileh), infoHeader(infoh)
{
    this->width=infoh.biWidth;
    this->height=infoh.biHeight;
    int tmpBytes=width*sizeof(rgbTriple);
    if(tmpBytes%4!=0)
    {
        this->padBytes=(tmpBytes/4+1)*4-tmpBytes;
    }
    else
        this->padBytes=0;
    this->memory();
}

bool Bmp::setPixel(int x, int y, rgbTriple color)
{
    if(x<0||x>=height||y<0||y>=width)
        return false;
    datas[x][y]=color;
    return true;
}

bool Bmp::setNormalPixel(int x, int y, rgbTriple color)
{
    if(x<0||x>=height||y<0||y>=width)
        return false;
    datas[height-x-1][y]=color;
    return true;
}

void Bmp::resize(int theight, int twidth)
{
    //to do
}

void Bmp::save(const char *filename)
{
    FILE* svfile=fopen(filename, "wb");
    fwrite(&fileHeader, sizeof(BmpFileHeader), 1, svfile);
	fwrite(&infoHeader, sizeof(BmpInfoHeader), 1, svfile);
	for (int i = 0; i < height; i++)
	{
		fwrite(datas[i], sizeof(rgbTriple), width, svfile);
        if(padBytes)
        {
		    BYTE tmp = 0;
		    fwrite(&tmp, sizeof(BYTE), padBytes, svfile);
        }
    }
    fclose(svfile);
}

bool Bmp::read(const char *filename)
{

}

