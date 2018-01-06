#include "libbmp.h"
#include "stdio.h"

int main()
{
    Bmp a(256, 256);
    for(int i=0; i<a.height; i++)
        for(int j=0; j<a.width; j++)
        {
            rgbTriple tmp;
            tmp.rgbtRed=(BYTE)i;
            tmp.rgbtGreen=(BYTE)j;
            tmp.rgbtBlue=128;
            a.setNormalPixel(j,i,tmp);
        }
    a.save();
    return 0;
}