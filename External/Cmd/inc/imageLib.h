/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/

#ifndef IMAGE_LIB_H
#define IMAGE_LIB_H
#ifndef CMD_LIB_H
	#include"cmdlib.h"
#endif
#include<stddef.h>
#include<stdio.h>

#ifdef __cplusplus
extern "C"{
#endif
/*
	// load texture
*/
int LoadTexture(const char* cfilename, unsigned char** pixeldata, unsigned int* iwidth, unsigned int* iheight, unsigned int* bytesPerPixel);
int SaveTexture(const char* cfilename,const unsigned char* pixeldata, unsigned int iwidth, unsigned int iheight, unsigned int bytesPerPixel);
/*
	//
*/
void LoadBMP(const char* cfilename, unsigned char** pixeldata, unsigned int* width, unsigned int* height, unsigned int* bytesPerPixel);
void SaveBMP(const char* cfilename,const unsigned char*  pixeldata, unsigned int width, unsigned int height, unsigned int  bytesPerPixel);

/*
	// TGA (True 
*/
void LoadTGA(const char* cfilename, unsigned char** pixeldata, unsigned int* width, unsigned int* height, unsigned int*bytesPerPixel);
void SaveTGA(const char* cfilename,const unsigned char*  pixeldata, unsigned int  width, unsigned int  height, unsigned int bytesPerPixel);

void LoadTGABuffer ( unsigned char *buffer, unsigned char **pic,unsigned int *width,unsigned int *height,int*bitsPerPixel);

/*
	// JPEG || JPG
*/
void LoadJPG(const char* cfilename, unsigned char** pixeldata, unsigned int* width, unsigned int* height, unsigned int* bytesPerPixel);
void SaveJPG(const char* cfilename,const unsigned char*  pixeldata, unsigned int  width, unsigned int  height, unsigned int bytesPerPixel);

/*
	// PNG
*/
void LoadPng(const char* cfilename, unsigned char** pixeldata, unsigned int* width, unsigned int* height, unsigned int* bytesPerPixel);
void SavePng(const char* cfilename,const unsigned char*  pixeldata, unsigned int  width, unsigned int  height, unsigned int bytesPerPixel);


/*
	// DDS	(Direct
*/
void LoadDDS(const char* cfilename, unsigned char** pixeldata, unsigned int* width, unsigned int* height, unsigned int* bytesPerPixel);
void SaveDDS(const char* cfilename,const unsigned char* pixeldata, unsigned int width, unsigned int height, unsigned int bytesPerPixel);

/*
	// TIF
*/
void LoadTIF(const char* cfilename, unsigned char** pixeldata, unsigned int* width, unsigned int* height, unsigned int* bytesPerPixel);
void SaveTIF(const char* cfilename,const unsigned char*  pixeldata, unsigned int  width, unsigned int  height, unsigned int  bytesPerPixel);



#define FLIP_RGBA 0x1
#define FLIP_BGRA 0x2 
/*
	// flip color
*/
void flipColor(unsigned char* pixeldata, unsigned int width, unsigned int height, unsigned int bytesPerPixels, unsigned int flip_flag);


#ifdef __cplusplus
};
#endif

#endif