/*********************
**  Mandelbrot fractal
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include <sys/types.h>

/*
This function returns the number of iterations before the initial point >= the threshold.
If the threshold is not exceeded after maxiters, the function returns 0.
*/
u_int64_t MandelbrotIterations(u_int64_t maxiters, ComplexNumber * point, double threshold)
{
    //YOUR CODE HERE
    ComplexNumber *product;
    ComplexNumber *sum = newComplexNumber(0, 0);

    for(int i = 0; i < maxiters; i++) {
        product = ComplexProduct(sum, sum);
        freeComplexNumber(sum);
        sum = ComplexSum(product, point);
        freeComplexNumber(product);

        if(threshold <= ComplexAbs(sum)) {
            freeComplexNumber(sum);
            return i + 1;
        }
    }

    freeComplexNumber(sum);
    return 0;
}

/*
This function calculates the Mandelbrot plot and stores the result in output.
The number of pixels in the image is resolution * 2 + 1 in one row/column. It's a square image.
Scale is the the distance between center and the top pixel in one dimension.
*/
void Mandelbrot(double threshold, u_int64_t max_iterations, ComplexNumber* center, double scale, u_int64_t resolution, u_int64_t * output){
    //YOUR CODE HERE
    for (size_t i = 0; i < resolution * 2 + 1; i++)
    {
        for (size_t j = 0; j < resolution * 2 + 1; j++)
        {
            ComplexNumber* point = newComplexNumber(Re(center) - scale + scale * j / resolution, Im(center) + scale - scale * i / resolution);
            output[i * (resolution * 2 + 1) + j] = MandelbrotIterations(max_iterations, point, threshold);
            freeComplexNumber(point);
        }
    }
}


