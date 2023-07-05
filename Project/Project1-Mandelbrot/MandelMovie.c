/*********************
**  Mandelbrot fractal movie generator
** clang -Xpreprocessor -fopenmp -lomp -o Mandelbrot Mandelbrot.c
** by Dan Garcia <ddgarcia@cs.berkeley.edu>
** Modified for this class by Justin Yokota and Chenyu Shi
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "ComplexNumber.h"
#include "Mandelbrot.h"
#include "ColorMapInput.h"
#include <sys/types.h>

void printUsage(char* argv[])
{
  printf("Usage: %s <threshold> <maxiterations> <center_real> <center_imaginary> <initialscale> <finalscale> <framecount> <resolution> <output_folder> <colorfile>\n", argv[0]);
  printf("    This program simulates the Mandelbrot Fractal, and creates an iteration map of the given center, scale, and resolution, then saves it in output_file\n");
}


/*
This function calculates the threshold values of every spot on a sequence of frames. The center stays the same throughout the zoom. First frame is at initialscale, and last frame is at finalscale scale.
The remaining frames form a geometric sequence of scales, so 
if initialscale=1024, finalscale=1, framecount=11, then your frames will have scales of 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1.
As another example, if initialscale=10, finalscale=0.01, framecount=5, then your frames will have scale 10, 10 * (0.01/10)^(1/4), 10 * (0.01/10)^(2/4), 10 * (0.01/10)^(3/4), 0.01 .
*/
void MandelMovie(double threshold, u_int64_t max_iterations, ComplexNumber* center, double initialscale, double finalscale, int framecount, u_int64_t resolution, u_int64_t ** output){
    //YOUR CODE HERE

	for (size_t i = 0; i < framecount; i++)
	{
		double scale = initialscale * pow(finalscale / initialscale, (double)i / (framecount - 1));
		output[i] = malloc(sizeof(u_int64_t) * (resolution * 2 + 1) * (resolution * 2 + 1));
		Mandelbrot(threshold, max_iterations, center, scale, resolution, output[i]);
	}
}

int P6colorpalette(char* colorfile, u_int64_t* iteration, int width, int height, char* outputfile)
{
	//YOUR CODE HERE
	int colorcount;
	uint8_t** color_input = FileToColorMap(colorfile, &colorcount);
	char* buf = malloc(sizeof(char) * 3 * width * height);

	FILE *fptr;
	if ((fptr = fopen(outputfile, "wb")) == NULL){
		printf("Error! opening file");
		return 1;
	}

	fprintf(fptr, "P6 %d %d 255\n", width, height);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			for (size_t k = 0; k < 3; k++) {
				if (iteration[i * width + j] == 0) {
					buf[i * width * 3 + j * 3 + k] = 0;
				}
				else {
					int color_index = (iteration[i * width + j] - 1) % colorcount;
					buf[i * width * 3 + j * 3 + k ] = (char)color_input[color_index][k];
				}
			}
		}
	}
	

	fwrite(buf, sizeof(char), width * height * 3, fptr);

	fclose(fptr);
	free(color_input);

	return 0;
}


/**************
**This main function converts command line inputs into the format needed to run MandelMovie.
**It then uses the color array from FileToColorMap to create PPM images for each frame, and stores it in output_folder
***************/
int main(int argc, char* argv[])
{
	//Tips on how to get started on main function: 
	//MandelFrame also follows a similar sequence of steps; it may be useful to reference that.
	//Mayke you complete the steps below in order. 

	//STEP 1: Convert command line inputs to local variables, and ensure that inputs are valid.
	/*
	Check the spec for examples of invalid inputs.
	Remember to use your solution to B.1.1 to process colorfile.
	*/

	//YOUR CODE HERE 
	int framecount;
	double threshold, center_real, center_imaginary, initialscale, finalscale;
	u_int64_t max_iterations, resolution;
	char *output_folder, *colorfile;

	char *pos = NULL;

	if (argc != 11) {
		printUsage(argv);
		return 1;
	}
	else {
		threshold = atof(argv[1]);
		max_iterations = strtoull(argv[2], &pos, 10);
		center_real = atof(argv[3]);
		center_imaginary = atof(argv[4]);
		initialscale = atof(argv[5]);
		finalscale = atof(argv[6]);
		framecount = atoi(argv[7]);
		resolution = strtoull(argv[8], &pos, 10);
		output_folder = argv[9];
		colorfile = argv[10];
	}

	if (threshold <= 0 || max_iterations <= 0 || finalscale <= 0 || initialscale <= 0) {
		printf("Invalid input: threshold, max iteration, or scale must exceed 0\n");
		printUsage(argv);
		return 1;
	}

	if (framecount > 10000 || framecount <= 0) {
		printf("Invalid input: framecount must be between 1 and 10000\n");
		printUsage(argv);
		return 1;
	}

	if (resolution < 0) {
		printf("Invalid input: resolution must be greater or equal than 0\n");
		printUsage(argv);
		return 1;
	}

	if (framecount == 1 && initialscale != finalscale) {
		printf("Invalid input: initialscale must equal finalscale when framecount is 1\n");
		printUsage(argv);
		return 1;
	}

	//STEP 2: Run MandelMovie on the correct arguments.
	/*
	MandelMovie requires an output array, so make sure you allocate the proper amount of space. 
	If allocation fails, free all the space you have already allocated (including colormap), then return with exit code 1.
	*/

	//YOUR CODE HERE 
	u_int64_t **output = malloc(sizeof(u_int64_t*) * framecount);

	if (output == NULL) {
		printf("Failed to allocate memory for output\n");
		return 1;
	}

	ComplexNumber* center = newComplexNumber(center_real, center_imaginary);

	MandelMovie(threshold, max_iterations, center, initialscale, finalscale, framecount, resolution, output);

	//STEP 3: Output the results of MandelMovie to .ppm files.
	/*
	Convert from iteration count to colors, and output the results into output files.
	Use what we showed you in Part B.1.2, create a seqeunce of ppm files in the output folder.
	Feel free to create your own helper function to complete this step.
	As a reminder, we are using P6 format, not P3.
	*/

	//YOUR CODE HERE 
	for(size_t i = 0; i < framecount; i++)
	{
		char *output_filename = malloc(sizeof(char) * 100);
		sprintf(output_filename, "%s/frame%05zu.ppm", output_folder, i);
		P6colorpalette(colorfile, output[i], resolution * 2 + 1, resolution * 2 + 1, output_filename);
		free(output_filename);
		printf("%ld\n", i);
	}

	//STEP 4: Free all allocated memory
	/*
	Make sure there's no memory leak.
	*/
	//YOUR CODE HERE 

	for (size_t i = 0; i < framecount; i++)
	{
		free(output[i]);
	}
	free(output);
	free(center);

	return 0;
}

