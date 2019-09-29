/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Fall 2017                     */
/*                                                                   */
/* Author: Tim Schmidt                                               */
/* Date: 11/09/2017                                                  */
/*                                                                   */
/* ImageList.c: source file for image list manipulations             */
/*                                                                   */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"

/* Create a new image entry */
IENTRY *CreateImageEntry(void)
{
	IENTRY *image =(IENTRY*)malloc(sizeof(IENTRY));
	image->RGBImage = NULL;
	image->YUVImage = NULL;
	image->Next = NULL;
	image->Prev = NULL;
	image->List = NULL;
	return image;

}

/* Delete image entry (and image objects)*/
void DeleteImageEntry(IENTRY *entry)
{
	assert(entry->RGBImage);
	assert(entry->YUVImage);

	DeleteImage(entry->RGBImage);
	entry->RGBImage = NULL;
	DeleteYUVImage(entry->YUVImage);
	entry->YUVImage = NULL;
	entry->Next = NULL;
	entry->Prev = NULL;
	entry->List = NULL;
	free(entry);		
}

/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *list = (ILIST*)malloc(sizeof(ILIST));
	list->First = NULL;
	list->Last = NULL;
	list->length = 0; 
	return list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
	IENTRY *temp = NULL;
	IENTRY *curr = list->First;
	while (curr)
	{
		temp = curr->Next;
		assert(curr);
		DeleteImageEntry(curr);
		curr = temp;
	}
	list->First = NULL;
	list->Last = NULL;
	free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, IMAGE *RGBimage)
{
	IENTRY *entry = CreateImageEntry();
	entry->YUVImage = CreateYUVImage(RGBimage->W, RGBimage->H);
	assert(entry->YUVImage); 
	entry->RGBImage = RGBimage;
	if (list->Last)
	{
		entry->List = list;
		entry->Prev = list->Last;
		list->Last->Next = entry;
		entry->Next = NULL;
		list->Last = entry;
	}
	else
	{
		entry->List = list;
                entry->Prev = NULL;
                entry->Next = NULL;
                list->First = entry;
                list->Last = entry;
	}
	list->length++;			
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVIMAGE *YUVimage) // insert node into list
{
	IENTRY *entry = CreateImageEntry();
	entry->RGBImage = CreateImage(YUVimage->W, YUVimage->H);
	assert(entry->RGBImage);
        entry->YUVImage = YUVimage;
        if (list->Last)
        {
                entry->List = list;
                entry->Prev = list->Last;
                list->Last->Next = entry;
		entry->Next = NULL;
                list->Last = entry;
        }
	else
	{
		entry->List = list;
                entry->Prev = NULL;
                entry->Next = NULL;
                list->First = entry;
                list->Last = entry;
	}
        list->length++;
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	unsigned int newFrameNum = 0;
	unsigned int counter = 0;
	IENTRY *curr = NULL; /* current entry in the list */
	IENTRY *prev = NULL; /* previous kept entry in the list */
	IENTRY *next = NULL; /* next entry in the list */

	assert(list);
	assert(factor > 0);

	curr = list->First;

	while (curr != NULL) {
		next = curr->Next;

		if (counter % factor == 0) {
			newFrameNum ++;

			curr->Prev = prev;
			if (prev != NULL) {
				prev->Next = curr;
			}
			prev = curr;
		} else {
			if (curr->RGBImage != NULL) {
				DeleteImage(curr->RGBImage);
			}

			if (curr->YUVImage != NULL) {
				DeleteYUVImage(curr->YUVImage);
			}

			curr->List = NULL;
			curr->Next = NULL;
			curr->Prev = NULL;
			curr->RGBImage = NULL;
			curr->YUVImage = NULL;
			free(curr);
		}

		curr = next;
		counter ++;
	}

	list->Last = prev;
	if (prev != NULL) {
		prev->Next = NULL;
	}
	list->length = newFrameNum;
}
/* Reverse an image list */
void ReverseImageList(ILIST *list) //traverse list in opposite direction (last->first)
{
	IENTRY *curr = list->Last;
	list->Last = list->First;
	list->First = curr;
	IENTRY *temp = NULL;
	while (curr)
	{
		temp = curr->Prev;
		curr->Prev = curr->Next;
		curr->Next = temp;
		curr = temp;
	}
}























/* EOF */
