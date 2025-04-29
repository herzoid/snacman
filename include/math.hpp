#pragma once

#include <complex>

struct Vect2f
{
    Vect2f()
        : x(0), y(0)
    {
    }

    Vect2f(int pX, int pY)
        : x(pX), y(pY)
    {
    }

    int x, y;
};

int mandelbrot(std::complex<double> c, int maxIter);