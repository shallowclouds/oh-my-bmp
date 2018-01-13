
#include <math.h>
#include "constant.h"
#include <cstdlib>
#include <vector>
// #include "headers/mingw.thread.h"
#include <thread>
#include "libbmp.h"

#define MAX_THREAD 8

double sample(double x, double y);
double trace(double x, double y, double direcX, double direcY);
double circleSDF(double x, double y, double cx, double cy, double r);
void render(Bmp* place, int from, int to);
void light2d();

int main(void)
{
    light2d();
    return 0;
}

void light2d()
{
    int now = clock() / CLOCKS_PER_SEC;
    Bmp scene(1024, 1024);
    std::vector<std::thread*> renderLines;
    for(int i=0; i<MAX_THREAD; i++)
    {
        std::thread* tmp=new std::thread(render, &scene, i*scene.height / MAX_THREAD, fmin( (i+1) * scene.height / MAX_THREAD-1, scene.height-1));
        renderLines.push_back(tmp);
    }
    for (auto i = renderLines.begin(); i != renderLines.end(); i++)
    {
        (*i)->join();
        delete (*i);
    }
    scene.save("multi.bmp");
    now = clock() / CLOCKS_PER_SEC-now;
    printf("Rendering cost %d s.\n", now);
}

void render(Bmp* place, int from, int to)
{
    printf("thread starts: %d %d\n", from, to);
    for(int y=from; y<=to; y++)
    {
        for(int x=0; x<place->width; x++)
        {
            rgbTriple color;
            color.rgbtBlue=color.rgbtGreen=color.rgbtRed=
            (BYTE)(fminf(sample((double)x / place->width, (double)y / place->height) * 255.0f, 255.0f));
            color.rgbtBlue*=0.6;
            place->setNormalPixel(x, y, color);
        }
    }
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
