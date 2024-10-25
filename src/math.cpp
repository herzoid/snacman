#include "../include/math.hpp"

int mandelbrot(std::complex<double> c, int maxIter)
{
    std::complex<double> z = 0;
    int n = 0;
    while (abs(z) <= 2 && n < maxIter)
    {
        z = z * z + c;
        n++;
    }
    return n;
}