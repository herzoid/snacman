#pragma once

#include <complex>

struct Vect2f
{
    Vect2f()
        : x(0.0f), y(0.0f)
    {
    }

    Vect2f(float pX, float pY)
        : x(pX), y(pY)
    {
    }

    float x, y;
};

int mandelbrot(std::complex<double> c, int maxIter);