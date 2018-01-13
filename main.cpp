#include "libbmp.h"
#include "stdio.h"
#include "math.h"
#include "light.h"
#include <ctime>

void sample();
void geo();

int main()
{
    light2d();
    
    // sample();
    return 0;
}

void geo()
{
    Bmp circle(4096,4096);
    double PI=3.14159269f;
    rgbTriple tmp;
    tmp.rgbtRed=102;
    tmp.rgbtGreen=153;
    tmp.rgbtBlue=51;
    int zx=circle.width/2, zy=circle.height/2;
    double R=1000.0f;
    for(double ang=0; ang<=2*PI; ang+=1e-6)
    {
        int tx=zx+R*sin(8*ang)*cos(ang), ty=zy+R*sin(8*ang)*sin(ang);
        circle.setNormalPixel(tx, ty, tmp);
    }
    circle.save("geo.bmp");
}

void sample()
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
    a.save("sample.bmp");
}
