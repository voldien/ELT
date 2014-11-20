/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef POLY_LIB_H
#define POLY_LIB_H
#ifndef MATH_LIB_H
	#include"mathlib.h"
#endif
#ifndef CMD_LIB_H
	#include"cmdlib.h"
#endif
#ifdef __cplusplus
extern "C"{
#endif
#define _VERTEX 0x1
#define _UV 0x2
#define _NORMAL 0x4
#define _TANGENT 0x8
#define _VERTEXCOLOR 0x10
#define _BONE
#define _ALL (unsigned int)(-1)

#define VERTEX_SIZE (0x3 * sizeof(float))
#define UV_SIZE (0x2 * sizeof(float))
#define NORMAL_SIZE (0x3 * sizeof(float))
#define TANGENT_SIZE (0x3 * sizeof(float))
#define VERTEXCOLOR_SIZE (0x4 * sizeof(float))
#define BONE_SIZE(num_bone)	(num_bone * (0x1 * sizeof(unsigned int) + sizeof(float) * 0x1))

#define TEMP(x,y) ( ( ( x ) & ( y ) )/ ( y ) )
#define EXPRESSION(x,y) ( ( ( x ) & ( y ) ) != 0 ? 1 : 0)
/*	get vertex size in bytes*/
#define _VERTEX_SIZE(x) (TEMP(x,_VERTEX) * VERTEX_SIZE + TEMP(x,_UV) * UV_SIZE + TEMP(x,_NORMAL) * NORMAL_SIZE + TEMP(x,_TANGENT) * TANGENT_SIZE + TEMP(x,_VERTEXCOLOR) * VERTEXCOLOR_SIZE)
/*	get indices element size in bytes*/
#define _INDICES_SIZE(x) ((( ( x ) > USHRT_MAX) ? 0x6 : 0x0) ^ (( ( x ) > UCHAR_MAX) ? 0x3 : 0x0) ^ (( ( x ) < UCHAR_MAX) ? 0x1 : 0x1))
/*
struct mesh_def{
	vec3_t vertex;
	vec2_t uv;
	vec3_t normal;
	vec3_t tangent;
};*/

void LoadOBJ(const char* cfilename, float** vertexData,unsigned char** indices, unsigned int* num_vertex, unsigned int* num_indices,unsigned int u_generate_flag);
void SaveOBJ(const char* cfilename, float* vertexdata, unsigned char* indices, unsigned int num_vertex, unsigned int num_indices,unsigned int stride, unsigned int indices_size, unsigned int igenerate_flag);

void Load3DS(const char* cfilename, float** vertexData, unsigned char** indices, unsigned int* num_vertex, unsigned int* num_indices,unsigned int u_generate_flag);
void Save3DS(const char* cfilename, float** vertexData, unsigned int** indices, unsigned int num_vertex, unsigned int num_indices,unsigned int u_generate_flag);

/*
	// PMX
*/
void LoadPMX(const char* cfilename, float** vertexData, unsigned char** indices, unsigned int* num_vertex, unsigned int* num_indices,unsigned int u_generate_flag);
void SavePMX(const char* cfilename, float* vertexdata, unsigned char* indices, unsigned int num_vertex, unsigned int num_indices);

/*
	// 3d gemoetry math
*/

void compute_BBox(const float* data, unsigned int stride, unsigned int idatasize, vec3_t size, vec3_t center);
//void compute_BSphere(const float* data, unsigned int stride, unsigned int idatasize, vec3_t center, float* radius);

void compute_normal(float** vertexdata,unsigned char*indices,unsigned int stride, unsigned int idatasize,unsigned int normal_offset);
void compute_normal_smooth(float** data,unsigned int istride, unsigned int idatasize, unsigned int normal_offset, float angle);
void compute_tangent(void** vertexdata,unsigned int istride, unsigned int ioffset, unsigned int idatasize);
void compute_uv_planar(float**data);
void compute_uv_spherical(float** data);
void compute_uv_rotate(float** data, vec2_t rotation_origion, float radias);

void compute_scale(float**vertexData,unsigned int istride, unsigned int idatasize,const vec3_t scale);
void compute_translation(float** vertexData,unsigned int istride, unsigned int idatasize,const vec3_t translation);
void compute_rotationq(float** vertexData, unsigned int istride, unsigned int idatasize,const vec4_t quaterion);

void compute_rotation_x(float** vertexData, unsigned int istride, unsigned int idatasize,float rot_x);
void compute_rotation_y(float** vertexData, unsigned int istride, unsigned int idatasize,float rot_y);
void compute_rotation_z(float** vertexData, unsigned int istride, unsigned int idatasize,float rot_z);

#ifdef __cplusplus
}
#endif
#endif