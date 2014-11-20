/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef Procedural_
#define Procedural_
#ifndef MATH_LIB_H
	#include"mathlib.h"
#endif
#ifndef POLY_LIB_H
	#include"polylib.h"
#endif

#ifdef __cplusplus
extern "C"{
#endif

//	struct frustum{float fov,aspect,near,far;};
/*
	// produceral geometry 
*/
/*	vertex only	*/
void procedural_grid_2d(float** vertexData, unsigned int* num_vertex, int inum_verticl, int inum_horizontal, float fsize, unsigned int u_generate_flag);
void procedural_grid_3d(float** vertexData, unsigned int* num_vertex, int inum_verticl, int inum_horizontal, int inum_depth,float fsize,unsigned int u_generate_flag);
void procedural_grid_box(float** vertexData, unsigned int* num_vertex, int inum_verticl, int inum_horizontal, int inum_depth,float fsize,unsigned int u_generate_flag);
void procedural_bound_box(float**vertexData,unsigned char** indices, unsigned int* num_vertex,unsigned int* num_indices, unsigned int u_generate_flag);
void procedural_frustum(float**vertexData,unsigned char** indices, unsigned int* num_vertex,unsigned int* num_indices, unsigned int u_generate_flag);
/*	vertex & indices	*/
void procedural_sphere(float** vertexData,unsigned char** indices, unsigned int* num_vertex, unsigned int* num_indices, int pointRows, int pointsPerRow, unsigned int u_generate_flag);
void procedural_cube(float** vertexData,unsigned char** indices, unsigned int* num_vertex, unsigned int* num_indices, int row, int coloum,int depth, unsigned int u_generate_flag);
void procedural_cone(float** vertexData,unsigned char** indices, unsigned int* inum_vertex, unsigned int* inum_indices,float f_innerRadius,float f_outerRadius, unsigned int isides, unsigned int irings, unsigned int u_generate_flag);
void procedural_quad(float** vertexData, unsigned char** indices, unsigned int* inum_vertex, unsigned int *inum_indices,signed int x_vertical, signed int y_horizontal, unsigned int u_generate_flag);
void procedural_torus(float** vertexData, unsigned char** indices, unsigned int* inum_vertex, unsigned int* inum_indices,float f_innerRadius,float f_outerRadius, unsigned int isides, unsigned int irings, unsigned int u_generate_flag);
void procedural_capsule(float** vertexData, unsigned char** indices, unsigned int* inum_vertex, unsigned int* inum_indices,float f_innerRadius,float f_outerRadius, unsigned int isides, unsigned int irings, unsigned int u_generate_flag);
void procedural_cylinder(float** vertexData,unsigned char** indices, unsigned int* inum_vertex, unsigned int* inum_indices,float f_radius, unsigned int isides, unsigned int irings,unsigned int i_generate_flag);
void procedural_terrain(float** vertexData, unsigned char** indices, unsigned int* inum_vertex,unsigned int* inum_indices,const unsigned char* iheightdata, unsigned int iwidth, unsigned int iheight, unsigned int i_generate_flag);

void procedural_march(float** vertexData, unsigned char** indices, unsigned int* inum_vertex, unsigned int* inum_indices);

void smooth_terrain(float** vertexData,int passes, unsigned int iwidth, unsigned int iheight,unsigned int i_generate_flag);



/*
	// produceral texture
*/

#define _RGB 0x1
#define _BGR 0x2
#define _GRAYSCALE 0x4
#define _RGBA 0x8
#define _BGRA 0x10
#define _TEXEL_SIZE_BYTES(x) ()
#define _TEXEL_SIZE_BITES(x) ( _TEXEL_SIZE_BYTES(x) * 8 )


void procedural_checker_texture(unsigned char** pixeldata, unsigned int iwidth,unsigned int iheight, unsigned int iflag);
void procedural_checker_texture2(unsigned char** pixeldata, unsigned int iwidth,unsigned int iheight, unsigned int iflag);
void procedural_grid_texture(unsigned char** pixeldata, unsigned int iwidth, unsigned int iheight, unsigned int flag);
void procedural_circle_texture(unsigned char** pixeldata, unsigned int iwidth, unsigned int iheight, unsigned int flag);
void procedural_wood_texture(unsigned char** pixeldata, unsigned int iwidth, unsigned int iheight, unsigned int iflag);

void procedural_normal_texture(unsigned char** pixeldata, unsigned int iwidth, unsigned int iheight, unsigned char* p_height_map, unsigned char iflag);
void resize_texture(unsigned char** pixeldata, unsigned char* texturedata, unsigned int texture_width,unsigned int texture_height);


#ifdef __cplusplus
};
#endif

#endif