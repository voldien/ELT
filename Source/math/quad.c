#include"quad.h"

#define QX 0x1
#define QY 0x2
#define QZ 0x3
#define QW 0x0

void quad_multi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]){
	// w
    out_quad[QW] = (lf_quad[QW] * rf_quad[QW]) - (lf_quad[QX] * rf_quad[QX]) - (lf_quad[QY] * rf_quad[QY]) - (lf_quad[QZ] * rf_quad[QZ]);
	// x
    out_quad[QX] = (lf_quad[QX] * rf_quad[QW]) + (lf_quad[QW] * rf_quad[QX]) + (lf_quad[QY] * rf_quad[QZ]) - (lf_quad[QZ] * rf_quad[QY]);
	// y
    out_quad[QY] = (lf_quad[QY] * rf_quad[QW]) + (lf_quad[QW] * rf_quad[QY]) + (lf_quad[QZ] * rf_quad[QX]) - (lf_quad[QX] * rf_quad[QZ]);
	// z
    out_quad[QZ] = (lf_quad[QZ] * rf_quad[QW]) + (lf_quad[QW] * rf_quad[QZ]) + (lf_quad[QX] * rf_quad[QY]) - (lf_quad[QY] * rf_quad[QX]);
}
void quad_multi_vec3(float lf_quat[4], vec3_t rf_vec,float out_quat[4]){
	out_quat[QX] =  (lf_quat[QW] * rf_vec[0]) + (lf_quat[QY] * rf_vec[2]) - (lf_quat[QZ] * rf_vec[1]);
	out_quat[QY] =  (lf_quat[QW] * rf_vec[1]) + (lf_quat[QZ] * rf_vec[0]) - (lf_quat[QX] * rf_vec[2]);
	out_quat[QZ] =  (lf_quat[QW] * rf_vec[2]) + (lf_quat[QX] * rf_vec[1]) - (lf_quat[QY] * rf_vec[0]);
	out_quat[QW] = -(lf_quat[QX] * rf_vec[0]) - (lf_quat[QY] * rf_vec[1]) - (lf_quat[QZ] * rf_vec[2]);
}


void quad_add_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]){
	out_quad[QW] = lf_quad[0] + rf_quad[0];
	out_quad[QX] = lf_quad[1] + rf_quad[1];
	out_quad[QY] = lf_quad[2] + rf_quad[2];
	out_quad[QZ] = lf_quad[3] + rf_quad[3];
}
void quad_sub_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]){
	out_quad[QW] = lf_quad[QW] - rf_quad[QW];
	out_quad[QX] = lf_quad[QX] - rf_quad[QX];
	out_quad[QY] = lf_quad[QY] - rf_quad[QY];
	out_quad[QZ] = lf_quad[QZ] - rf_quad[QZ];
}
void quad_divi_quad(const float lf_quad[4],const float rf_quad[4], float out_quad[4]){
	out_quad[QW] = lf_quad[QW] / rf_quad[QW];
	out_quad[QX] = lf_quad[QX] / rf_quad[QX];
	out_quad[QY] = lf_quad[QY] / rf_quad[QY];
	out_quad[QZ] = lf_quad[QZ] / rf_quad[QZ];
}


/*
extern void quad_direction(float lf_quad[4], vec3_t dir){
	float quad[4];
	float quad_t[4];
	float quad_t2[4];
	vec3_t forward = NVEC3_UNIT_Z;
	mulit_quat_vec3(lf_quad,forward,quad_t2);
	QuaternionCopy(lf_quad,quad);
	//quat_multiplyVec3(lf_quad,forward,dir);
	//return;
	QuaternionInverse(quad);
	multi_quad(quad_t2,quad,quad_t);
	dir[0] = quad_t[QX];
	dir[1] = quad_t[QY];
	dir[2] = quad_t[QZ];
}
extern void quad_directionv(float lf_quad[4], vec3_t dir,const vec3_t _dir){
	float quad[4];
	float quad_t[4];
	float quad_t2[4];

	//quat_multiplyVec3(lf_quad,_dir,dir);
	//return;
	//VectorNegate(_dir);
	mulit_quat_vec3(lf_quad,_dir,quad_t2);
	QuaternionCopy(lf_quad,quad);
	QuaternionConjugate(quad);
	multi_quad(quad_t2,quad,quad_t);
	dir[0] = quad_t[QX];
	dir[1] = quad_t[QY];
	dir[2] = quad_t[QZ];
}*/



/**
	quaternion x rotation in radian
*/
//float quad_pitch(const float lf_quad[4]){
//    	return (float)asinf(-2.0f * (lf_quad[QZ] * lf_quad[QY] + lf_quad[QW] * lf_quad[QX]));
//}
/**
	quaternion y rotation in radian
*/
//float quad_yaw(const float lf_quad[4]){
//    return (float)atan2f(2.0f * (lf_quad[QW] * lf_quad[QX] + lf_quad[QY] * lf_quad[QW]),( 1.0f - ( 2.0f * (lf_quad[QX] * lf_quad[QX] + lf_quad[QY] * lf_quad[QY]))));
//}
/**
	quaternion z rotation in radian
*/
//float quad_roll(const float lf_quad[4]){
//	return (float)atan2f(2.0f * (lf_quad[QW] * lf_quad[QZ] + lf_quad[QX] * lf_quad[QY]), 1.0f - (2.0f * (lf_quad[QY] * lf_quad[QY] + lf_quad[QZ] * lf_quad[QZ])));
//}
