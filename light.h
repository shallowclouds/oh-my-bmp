#ifndef LIGHT_H
#define LIGHT_H

#include "libbmp.h"
#include "math.h"
#include "constant.h"
#include "stdlib.h"

double sample(double x, double y);
double trace(double x, double y, double direcX, double direcY);
double circleSDF(double x, double y, double cx, double cy, double r);

void light2d()
{
    Bmp scene(1024, 1024);

    for(int y=0; y<scene.height; y++)
        for(int x=0; x<scene.width; x++)
        {
            rgbTriple color;
            color.rgbtBlue=color.rgbtGreen=color.rgbtRed=
            (BYTE)(fminf(sample((double)x / scene.width, (double)y / scene.height) * 255.0f, 255.0f));
            color.rgbtBlue*=0.6;
            scene.setNormalPixel(x, y, color);
        }

    scene.save("light.bmp");
}

double sample(double x, double y)
{
    double sum=0.0f;
    int n=64;
    for(int i=0; i<n; i++)
    {
        double tmp=Pi2 * (i+(double)rand()/RAND_MAX)/n;
        sum+=trace(x, y, cosf(tmp), sinf(tmp));
    }
    return sum/n;
}

double trace(double x, double y, double direcX, double direcY)
{
    const int MAX_STEP=10;
    const double MAX_DISTANCE=2.0f;
    const double EPSILON=1e-6f;
    double t=0.0f;
    for(int i=0; i<MAX_STEP && t<MAX_DISTANCE; i++)
    {
        double sd=circleSDF(x+direcX*t, y+direcY*t, 0.5f, 0.5f, 0.1f);
        if(sd<EPSILON)
            return 2.0f;
        t+=sd;
    }
    return 0.0f;
}

double circleSDF(double x, double y, double cx, double cy, double r)
{
    double ux=x-cx, uy=y-cy;
    return sqrtf(ux*ux+uy*uy)-r;
}


#endif