#!/bin/bash


CC := gcc
RM := rm -rf
CLFAGS := -Wall -O2
CLIBS := -lEngineEx -lGL -lGLEW


all : main
	echo -en "finished $(du -h $@) "

main : main.c
	$(CC) $(CFLAGS) $^ -o $@ $(CLIBS) 

clean : 
	$(RM) *.o
