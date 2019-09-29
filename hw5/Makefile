# Makefile for hw4, EECS22 Fall 2017 fall 
# Author: Huan Chen
# Modified by: Mihnea Chirila
# Modification: Ali Nickparsa 11/11/2018
# Date:   11/01/2017
CC     = gcc
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall -lm

OBJS = MovieLab.o FileIO.o Image.o MovieIO.o
DEPS = Image.h ImageList.h DIPs.h FileIO.h MovieIO.h Movie.h IterativeFilter.h Constants.h

DESIGN = MovieLab
all: $(DESIGN)
MovieLab: $(OBJS) libFilter.a
	$(CC) $(LFLAGS) $(OBJS) -L. -lFilter -o MovieLab

libFilter.a: DIPs.o ImageList.o Movie.o IterativeFilter.o
	ar rc libFilter.a DIPs.o ImageList.o Movie.o IterativeFilter.o
	ranlib libFilter.a

MovieLab.o: MovieLab.c $(DEPS)
	$(CC) $(CFLAGS) MovieLab.c -o MovieLab.o
FileIO.o: FileIO.c FileIO.h Image.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o
DIPs.o: DIPs.c DIPs.h Image.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o
Image.o: Image.c Image.h
	$(CC) $(CFLAGS) Image.c -o Image.o
ImageList.o: ImageList.c ImageList.h Image.h
	$(CC) $(CFLAGS) ImageList.c -o ImageList.o
Movie.o: Movie.c Movie.h ImageList.h
	$(CC) $(CFLAGS) Movie.c -o Movie.o
IterativeFilter.o: IterativeFilter.c IterativeFilter.h Image.h Movie.h
	$(CC) $(CFLAGS) IterativeFilter.c -o IterativeFilter.o
MovieIO.o: MovieIO.c MovieIO.h Movie.h Image.h
	$(CC) $(CFLAGS) MovieIO.c -o MovieIO.o


clean:
	rm -f *.o *.a $(DESIGN) `find . -name '*.yuv'`
