#include"math/quad.h"

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


void quad_axis_angle(float lf_quad[4],const vec3_t axis, float f_angle){
	const float half_angle = sinf(f_angle * 0.5f);
	lf_quad[QX] = axis[0] * half_angle;
	lf_quad[QY] = axis[1] * half_angle;
	lf_quad[QZ] = axis[2] * half_angle;
	lf_quad[QW] = cosf(half_angle);
}
/*
	generate quaternion out of euler rotation
*/
void quad_axis(float lf_quad[4], float pitch_rad,float yaw_rad,float roll_rad){
	const float num1 = roll_rad * 0.5f;
	const float num2 = (float)sinf((float)num1);
	const float num3 = (float)cosf((float)num1);
	const float num4 = pitch_rad * 0.5f;
	const float num5 = (float)sinf((float)num4);
	const float num6 = (float)cosf((float)num4);
	const float num7 = yaw_rad * 0.5f;
	const float num8 = (float)sinf((float)num7);
	const float num9 = (float)cosf((float)num7);

	lf_quad[QX] = (float)((double)num9 * (double)num5 * (double)num3 + (double)num8 * (double)num6 * (double)num2);
	lf_quad[QY] = (float)((double)num8 * (double)num6 * (double)num3 - (double)num9 * (double)num5 * (double)num2);
	lf_quad[QZ] = (float)((double)num9 * (double)num6 * (double)num2 - (double)num8 * (double)num5 * (double)num3);
	lf_quad[QW] = (float)((double)num9 * (double)num6 * (double)num3 + (double)num8 * (double)num6 * (double)num2);
}



void quad_direction(float lf_quad[4], vec3_t dir){
	float quad[4];
	float quad_t[4];
	float quad_t2[4];
	vec3_t forward = NVEC3_UNIT_Z;
	//mulit_quat_vec3(lf_quad,forward,quad_t2);
	QuaternionCopy(lf_quad,quad);
	//quat_multiplyVec3(lf_quad,forward,dir);
	//return;
	QuaternionInverse(quad);
	//multi_quad(quad_t2,quad,quad_t);
	dir[0] = quad_t[QX];
	dir[1] = quad_t[QY];
	dir[2] = quad_t[QZ];
}
void quad_directionv(float lf_quad[4], vec3_t dir,const vec3_t _dir){
	float quad[4];
	float quad_t[4];
	float quad_t2[4];

	//quat_multiplyVec3(lf_quad,_dir,dir);
	//return;
	//VectorNegate(_dir);
	//mulit_quat_vec3(lf_quad,_dir,quad_t2);
	QuaternionCopy(lf_quad,quad);
	QuaternionConjugate(quad);
	quad_multi_quad(quad_t2,quad,quad_t);
	dir[0] = quad_t[QX];
	dir[1] = quad_t[QY];
	dir[2] = quad_t[QZ];
}



/**
	quaternion x rotation in radian
*/
float quad_pitch(const float lf_quad[4]){
    	return (float)asinf(-2.0f * (lf_quad[QZ] * lf_quad[QY] + lf_quad[QW] * lf_quad[QX]));
}
/**
	quaternion y rotation in radian
*/
float quad_yaw(const float lf_quad[4]){
    return (float)atan2f(2.0f * (lf_quad[QW] * lf_quad[QX] + lf_quad[QY] * lf_quad[QW]),( 1.0f - ( 2.0f * (lf_quad[QX] * lf_quad[QX] + lf_quad[QY] * lf_quad[QY]))));
}
/**
	quaternion z rotation in radian
*/
float quad_roll(const float lf_quad[4]){
	return (float)atan2f(2.0f * (lf_quad[QW] * lf_quad[QZ] + lf_quad[QX] * lf_quad[QY]), 1.0f - (2.0f * (lf_quad[QY] * lf_quad[QY] + lf_quad[QZ] * lf_quad[QZ])));
}

void quad_slerp(const float lf_quad[4],const float rf_quad[4], float outf_quad[4],float f_time){

}

