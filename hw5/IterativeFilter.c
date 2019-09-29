/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2018                     */
/*                                                                   */
/* Author: Jordan Bonecutter                                         */
/*                                                                   */
/* IterativeFilter.c: file for iterative filters                     */
/*                                                                   */
/*********************************************************************/

#include "IterativeFilter.h"
#include "assert.h"

MOVIE *doIterativeFilter(IMAGE *image, iterableFilter filter, float start, float end, float change)
{
 	MOVIE *movie = CreateMovie();
	assert(movie);
	IMAGE *temp;
	if (start < end)
	{
		for (float x = start; x <= end; x += change)
		{
			temp = CopyImage(image);
			assert(temp);
			temp = filter(temp, x);
			AppendRGBImage(movie->Frames, temp);
			RGB2YUVMovie(movie);
		}
		temp = NULL;
	}
	else
	{
		for (float x = start; x >= end; x -= change)
                {
                        temp = CopyImage(image);
			assert(temp);
                        temp = filter(temp, x);
                        AppendRGBImage(movie->Frames, temp);
                        RGB2YUVMovie(movie);
                }
                temp = NULL;
	}
	return movie;
}
