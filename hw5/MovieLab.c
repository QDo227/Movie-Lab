/*********************************************************************/
/* PhotoLab.c: assignment 5 for EECS 22, Fall 2018                   */
/*                                                                   */
/* modifications: Mihnea Chirila                                     */
/* 09/27/17 RD  adjusted for lecture usage                           */
/* 10/1/18 MC    adjusted for F18                                    */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 *  
 *******************************
 * First Name : Quang
 * Last Name: Do
 * UCInet ID: 35806780
 *       
*/

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"
#include "DIPs.h"
#include "Movie.h"
#include "Constants.h"
#include "Image.h"
#include "MovieIO.h"
#include "IterativeFilter.h"

int main(int argc, char *argv[])
{
//	printf("num = %i\n", argc);
	MOVIE *movie;
	IMAGE *image = NULL;
	float start;
	float end;
	float step;
	char *fileim = "";// import file
	char *fileex; // export file
	int rtrue = 0; 
	int itrue = 0; // check if image is created
	int frameNum;
	int width;
	int height;
	iterableFilter filter;
	for (int i = 1; i < argc; i+=2) // scan for all key characters.
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			image = LoadImage(argv[i+1]);
			itrue = 1;
		}
		else if (strcmp(argv[i], "-o") == 0)
			fileex = argv[i+1];
		else if (strcmp(argv[i], "-start=") == 0)
			start = atof(argv[i+1]);
		else if (strcmp(argv[i], "-end=") == 0)
			end = atof(argv[i+1]);	
		else if (strcmp(argv[i], "-step=") == 0)
                        step = atof(argv[i+1]);
		else if (strcmp(argv[i], "-f") == 0)
			frameNum = atoi(argv[i+1]);
		else if (strcmp(argv[i], "-hue") == 0)
		{
			filter = HueRotate;
			movie = doIterativeFilter(image, filter, start, end, step);
		}
		else if (strcmp(argv[i], "-saturate") == 0)
                {
                        filter = Saturate;
                        movie = doIterativeFilter(image, filter, start, end, step);
                }
		else if (strcmp(argv[i], "-s") == 0)
                        sscanf(argv[i+1],"%dx%d", &width, &height);
		else if (strcmp(argv[i], "-m") == 0)
                        fileim = argv[i+1];
		else if (strcmp(argv[i], "-reverse") == 0)
                        rtrue = 1;
	}
	if (strcmp(fileim, "") != 0)
		movie = LoadMovie(fileim, frameNum, width, height);
	if (rtrue == 1) 
		ReverseImageList(movie->Frames);
	if (itrue == 1) //delete image if created
	{
		DeleteImage(image);
		image = NULL;
	}

	SaveMovie(fileex, movie);	
	printf("movie size: %ix%i\n", MovieWidth(movie), MovieHeight(movie));
	DeleteMovie(movie);
	movie = NULL;

	return 0;
}

/* EOF */
