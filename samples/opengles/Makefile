#!/bin/bash

CC=gcc
ifdef ComSpec	#	windows 
CLIBS=-lEngineEx -lm
CFLAGS=-Wall
else
CLIBS=-lEngineEx -lm
CFLAGS=-Wall
endif

all:
	echo "finished."

main : main.c 
	$(CC) $(CFLAGS) $@ -o main $(CLIBS)

clean:
	
