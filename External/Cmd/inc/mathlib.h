/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef MATH_LIB_H
#define MATH_LIB_H
#include<math.h>

// alignment of data
#ifdef _WIN32
	#define ALIGN(x) __declspec(align(x))
#else
	#define ALIGN(x)	__attribute__ ((aligned(x)))
#endif

#define QX 0x1
#define QY 0x2
#define QZ 0x3
#define QW 0x0

/*
	// double precision vector
*/	
#ifdef DOUBLEVEC_T
	typedef double vec_t;
#else
	typedef float vec_t;
#endif
/*
	//double precision matrix
*/
#ifdef DOUBLEMAT_T
	typedef double mvec_t;
#else
	typedef float mvec_t;
#endif
// vector2 = {x,y}
typedef vec_t vec2_t[2];
// vector2 = {x,y,z}
typedef vec_t vec3_t[3];
// vector2 = {x,y,z,w}
typedef vec_t vec4_t[4];
// quaternion = {w, x,y,z}
typedef vec_t quat_t[4];

typedef struct size_i{unsigned int width,height;}*Size_t;
typedef struct rect_decl{int x,y,width,height;}rect_t; 


// matrix = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
typedef vec_t vec4x4_t[4][4];
#define vec4x4 ALIGN(16) vec4x4_t
// matrix = {{0,0,0},{0,0,0},{0,0,0}};
typedef vec_t vec3x3_t[3][3];
#define vec3x3 ALIGN(9) vec3x3_t
// matrix = {{0,0},{0,0}};
typedef vec_t vec2x2_t[2][2];
#define vec2x2 ALIGN(4) vec2x2_t


// matrix = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
typedef vec_t vec16_t[16];
// matrix = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
typedef vec_t vec9_t[9];

/*
	
*/
#define VEC3_UNIT_X {1.0f, 0.0f, 0.0f}
#define VEC3_UNIT_Y {0.0f, 1.0f, 0.0f}
#define VEC3_UNIT_Z {0.0f, 0.0f, 1.0f}
#define VEC3_UNIT_W {0.0f, 0.0f, 0.0f, 1.0f}
#define NVEC3_UNIT_X {-1.0f, 0.0f, 0.0f}
#define NVEC3_UNIT_Y {0.0f, -1.0f, 0.0f}
#define NVEC3_UNIT_Z {0.0f, 0.0f, -1.0f}
#define NVEC3_UNIT_W {0.0f, 0.0f, 0.0f, -1.0f}


#define PI 3.14159265359F
#define EX_PI 3.14159265359F
#define PI_D 3.141592653589793238462
#define PI2 6.28318530718F
#define PI2_D 6.28318530718
#define THETA 1.57079632679F
#define THETAD 1.57079632679
#define E_E 2.7182818284F
#define E_E_D 2.7182818284
#define DEG2RAD( a ) ( ( (a) * PI ) / 180.0F )
#define RAD2DEG( a ) ( ( (a) * 180.0f ) / PI )

#define MIN(a,b)	( ( (a) > (b) ) ? (a) : (b) )
#define MAX(a,b)	( ( (a) < (b) ) ? (a) : (b) )
#define CLAMP(a,min,max)	(MAX( ( max ) ,MIN( ( min ) , ( a ) )))
#define LERP(a,b,t)	( ( (a) + ( (b) - (a) )*(t) )

#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define CrossProduct(x,y,c)	{c[0] = ((x[1] * y[2]) - (x[2] * y[1])); c[1] = ((x[2] * y[0]) - (x[0] * y[2])); c[2] = ((x[0] * y[1]) - (x[1] * y[0]));}
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}
#define VectorScale(a,b,c) {c[0]=b*a[0];c[1]=b*a[1];c[2]=b*a[2];}
#define VectorProduct(a,b,c) {c[0] = a[0]*b[0];c[1] = a[1]*b[1];c[2] = a[2]*b[2];}
#define VectorClear(x) {x[0] = x[1] = x[2] = 0;}
#define	VectorNegate(x) {x[0]=-x[0];x[1]=-x[1];x[2]=-x[2];}
#define VectorNormalize(x) {float length = VectorLength(x); x[0] /= length; x[1] /= length; x[2] /= length;}
#define VectorLength(x)	sqrtf((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]))
#define VectorLengthSqrt(x) ((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]))
#define VectorInverse(x)	{x[0] = 1.0f / x[0]; x[1] = 1.0f /x[1]; x[2] = 1.0 / x[2];}
#define VectorReflect(x,n,y)	{y[0] = 2.0f *( x[0] * n[0]) * n[0] - x[0];y[0] = 2.0f *( x[1] * n[1]) * n[1] - x[1];y[2] = 2.0f *( x[2] * n[2]) * n[2] - x[2];}
#define VectorOrthoNormalize(x,y) { float length;}
#define VectorProj(x,y,c)	{float lengthy = VectorLength(y);float dot = DotProduct(x,y); c[0] = dot * x[0] / lengthy;  c[1] = dot * x[1] / lengthy;  c[2] = dot * x[2] / lengthy; }
#define VectorLerp(x,y,t,c)	{}


#define QuaternionDirection(x)	{}
#define QuaternionConjugate(x)	{x[0] = -x[0];x[1] = x[1];x[2] = -x[2];}
#define QuaternionLength(x)	sqrtf((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]) + (x[3] * x[3]))
#define QuaternionLengthSqrt(x)	((x[0] * x[0]) + (x[1] * x[1]) + (x[2] * x[2]) + (x[3] * x[3]))
#define QuaternionNormalize(x)	{float length = QuaternionLength(x);x[0] /= length;x[1] /= length;x[2] /= length;x[3] /= length;}
#define QuaternionInverse(x)	{float length = QuaternionLength(x);x[0] /= length;x[1] /= length; x[2] /= length; x[3] /= length;}
#define QuaternionDot(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2] + x[3] * y[3])
#define QuaternionIdentity(x) {x[0] = 1.0f;x[1] = 0.0f;x[2] = 0.0f;x[3] = 0.0f;}
#define QuaternionCopy(a,b) {b[0] = a[0];b[1] = a[1];b[2] = a[2];b[3] = a[3];}
#define QuaternionYaw(lf_quad)  (float)atan2f(2.0f * (lf_quad[QUAD_W] * lf_quad[QUAD_X] + lf_quad[QUAD_Y] * lf_quad[QUAD_W]),( 1.0f - ( 2.0f * (lf_quad[QUAD_X] * lf_quad[QUAD_X] + lf_quad[QUAD_Y] * lf_quad[QUAD_Y]))))
#define QuaternionPitch(lf_quad) (float)asinf(-2.0f * (lf_quad[QUAD_Z] * lf_quad[QUAD_Y] + lf_quad[QUAD_W] * lf_quad[QUAD_X]))
#define QuaternionRoll(lf_quad) (float)atan2f(2.0f * (lf_quad[QUAD_W] * lf_quad[QUAD_Z] + lf_quad[QUAD_X] * lf_quad[QUAD_Y]), 1.0f - (2.0f * (lf_quad[QUAD_Y] * lf_quad[QUAD_Y] + lf_quad[QUAD_Z] * lf_quad[QUAD_Z])))

#ifdef __cplusplus
extern "C"{
#endif

// Get Next Power 2
int nextPower2(int n);
// Get Previous Power 2
int previousPower2(int n);
#define Nextpower2 nextPower2
#define PreviousPower2 previousPower2

double findnoise(double x);
double findnoise2(double x, double y);
double interpolate(double a, double b, double x);
double perlin_noise2(double x, double y);

double fade(double t);
double lerp(double t,double a, double b);
double grad(int hash, double x, double y, double z);
double perlin_noise3D(double x,double y, double z);

/*
	// 3d vector math
*/

void multi_vec3(void);
void linearInterp(vec3_t rf_vec3,vec3_t lf_vec3,float value,vec3_t outvalue);
void fcrossproduct(const vec3_t rf_vec3,const vec3_t lf_vec3, vec3_t out_vec3);
void calcuate_normal(vec3_t rf_vec3, vec3_t lf_vec3, vec3_t vec_out);
void calcuate_tangent(vec3_t rf_normal_vec3, vec3_t vec_out);
void calcuate_binormal(vec3_t rf_vec3, vec3_t lf_vec3, vec3_t vec_out);
void calcuate_bitangent(vec3_t rf_vec3, vec3_t lf_vec3, vec3_t vec_out);

/*
	// matrix 4x4
*/
void mulit_mat4_vec4(float lf_mat4[4][4], float rf_vec4[4],float out_vec4[4]);
/*	Multiplication*/
void mulit_mat4(const vec4x4_t lf_mat4,const vec4x4_t rf_mat4, vec4x4_t outf_mat4);
void divs_mat4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);
void addi_mat4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);
void subt_mat4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4);


void identity_mat4(vec4x4_t f_mat4);
void transpose_mat4(vec4x4_t f_mat4);
float determinant_mat4(vec4x4_t f_mat4);
void inverse_mat4(vec4x4_t f_mat4);

void decompose_mat4(const float f_mat4[4][4], vec3_t f_position, quat_t f_rotation, vec3_t f_scale);
// geometric projection.

void proj_mat4(vec4x4_t f_mat4, float f_fov, float f_aspect, float f_near, float f_far);
void orth_mat4(vec4x4_t f_mat4,float f_right, float f_left, float f_top, float f_bottom, float f_far,float f_near);

void unproj_mat4(vec4x4_t f_mat4);
// geometric transformation

void translation_mat4(vec4x4_t f_mat4,const vec3_t translation);
void translation_mat4v(float f_mat4[4][4],const vec3_t translation);
void scale_mat4(vec4x4_t f_mat4, vec3_t scale);

void translation_multi_mat4(vec4x4_t f_mat4, vec3_t translate);
void scale_multi_mat4(vec4x4_t f_mat4, vec3_t scale);

/*	Eular Rotation	*/
void rot_mat4(vec4x4_t f_mat4,float angle, vec3_t axis);
void rotationX_mat4(vec4x4_t f_mat4, float x_radi);
void rotationY_mat4(vec4x4_t f_mat4, float y_radi);
void rotationZ_mat4(vec4x4_t f_mat4, float z_radi);

void rotationQ_mat4(vec4x4_t f_mat4, float f_quad[4]);

/**/
void rotationx_multi_mat4(vec4x4_t f_mat4, float f_x_radi);
void rotationy_multi_mat4(vec4x4_t f_mat4, float f_y_radi);
void rotationz_multi_mat4(vec4x4_t f_mat4, float f_z_radi);

void rotationQ_multi_mat4(vec4x4_t f_mat4, float f_quad[4]);
void mat4_decompose_quad(vec4x4_t f_mat4, float f_quad[4]);


void lookat(vec4x4_t f_mat4, const vec3_t position, const vec3_t forward, const vec3_t up);

/*
	// quaternion
*/
void multi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);
void addi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);
void subt_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);
void divi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]);

void mulit_quat_vec3(float lf_quat[4], vec3_t rf_vec,float out_quat[4]);

void quad_direction(float lf_quad[4], vec3_t dir);
void quad_directionv(float lf_quad[4], vec3_t dir,const vec3_t _dir);
void quad_axis_angle(float lf_quad[4],const vec3_t axis, float f_angle);
void quad_axis(float lf_quad[4], float pitch_rad,float yaw_rad,float roll_rad);
void quad_lookrotation(float f_quad[4], vec3_t f_dir);

/*
	// quaternion x rotation in radian
*/
float quad_pitch(const float lf_quad[4]);
/*
	// quaternion y rotation in radian
*/
float quad_yaw(const float lf_quad[4]);
/*
	// quaternion z rotation in radian
*/
float quad_roll(const float lf_quad[4]);

// spherical linear interpolation
void slerp_quad(const float lf_quad[4],const float rf_quad[4], float outf_quad[4],float f_time);


// ray tracing
int lines_intersection(vec3_t pos1_1, vec3_t pos1_2,vec3_t pos2_1, vec3_t pos2_2,vec3_t pos);

int line_box_intersec(vec3_t pos,vec3_t dir,const vec3_t size,const vec3_t center);

int line_sphere_intersec(vec3_t pos, vec3_t dir, const vec3_t center, const vec3_t radius);


/*
	// clamp
*/
int clampi(int ivalue, int imin,int imax);
float clampf(float fvalue, float fmin,float fmax);
double clampd(double dvalue, double dmin,double dmax);
/*
	// linear interpolation
*/

float lerpf(float f_start, float f_end,float f_time);
double lerpd(double d_start, double d_end,double d_time);
int lerpi(int i_start, int i_end, float f_time);

#ifdef __cplusplus
}
#endif
#endif