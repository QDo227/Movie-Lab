/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* Movie.c: source file for basic movie manipulations                */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "Movie.h"

/* Allocate the memory space for the movie and the memory space */
/* for the frame list. Return the pointer to the movie. */
MOVIE *CreateMovie(void)
{
	MOVIE *movie = (MOVIE*)malloc(sizeof(MOVIE));
	movie->Frames = CreateImageList();
	return movie;
}

/* Release the memory space for the frame list. */
/* Release the memory space for the movie. */
void DeleteMovie(MOVIE *movie)
{
	assert(movie->Frames);

	DeleteImageList(movie->Frames);
	movie->Frames = NULL;
	free(movie);
}


int clip(int x)
{
        if (x < 0)
                return 0;
        else if (x > 255)
                return 255;
        else
                return x;
}

/* Convert a YUV movie to a RGB movie */
void YUV2RGBMovie(MOVIE *movie)
{
	IMAGE *image = movie->Frames->Last->RGBImage;
	YUVIMAGE *yuv = movie->Frames->Last->YUVImage;
	for (int x = 0; x < MovieWidth(movie); x++)
	{
		for (int y = 0; y < MovieHeight(movie); y++)
		{
			int C = GetPixelY(yuv, x, y) - 16;
			int D = GetPixelU(yuv, x, y) - 128;
			int E = GetPixelV(yuv, x, y) - 128;
			SetPixelR(image, x, y, clip(((298*C+409*E+128)>>8)));
                        SetPixelG(image, x, y, clip(((298*C-100*D-208*E+128)>>8)));
                        SetPixelB(image, x, y, clip(((298*C+156*D+128)>>8)));
		}
	}
	image = NULL;
	yuv = NULL;	
}

/* Convert a RGB movie to a YUV movie */
void RGB2YUVMovie(MOVIE *movie)
{
	IMAGE *image = movie->Frames->Last->RGBImage;
        YUVIMAGE *yuv = movie->Frames->Last->YUVImage;
        for (int x = 0; x < MovieWidth(movie); x++)
        {
                for (int y = 0; y < MovieHeight(movie); y++)
                {
                        int R = GetPixelR(image, x, y);
                        int G = GetPixelG(image, x, y);
                        int B = GetPixelB(image, x, y);
                        SetPixelY(yuv, x, y, clip(((66*R+129*G+25*B+128)>>8)+16));
                        SetPixelU(yuv, x, y, clip(((-38*R-74*G+112*B+128)>>8)+128));
                        SetPixelV(yuv, x, y, clip(((112*R-94*G-18*B+128)>>8)+128));
                }
        }
	image = NULL;
	yuv = NULL;

}

int MovieLength(const MOVIE *movie)
{
	return movie->Frames->length;
}

int MovieHeight(const MOVIE *movie)
{
	return movie->Frames->First->YUVImage->H;
}

int MovieWidth(const MOVIE *movie)
{
	return movie->Frames->First->YUVImage->W;

}
/* EOF */
