/*********************
**  Color Map generator
** Skeleton by Justin Yokota
**********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "ColorMapInput.h"


/**************
**This function reads in a file name colorfile.
**It then uses the information in colorfile to create a color array, with each color represented by an int[3].
***************/
uint8_t** FileToColorMap(char* colorfile, int* colorcount)
{
	//YOUR CODE HERE
	FILE *fptr;
    if ((fptr = fopen(colorfile, "r")) == NULL){
        printf("Error! opening file");
        exit(1);
    }
 
	if(fscanf(fptr, "%d", colorcount) != 1) {
		printf("Error! wrong format");
		exit(1);
	}

	uint8_t** ret = (uint8_t**)malloc(sizeof(uint8_t*) * *colorcount);

    for (size_t i = 0; i < *colorcount; i++)
	{
		ret[i] = (uint8_t*)malloc(sizeof(uint8_t) * 3);
		if(fscanf(fptr, "%hhu %hhu %hhu", &ret[i][0], &ret[i][1], &ret[i][2]) != 3) {
			printf("Error! wrong format");
			exit(1);
		}
	}

	fclose(fptr);
 
    return ret;
}


