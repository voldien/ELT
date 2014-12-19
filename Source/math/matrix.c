#include"matrix.h"
//__SSE4__ ||
//#define ENABLE_AVX
#ifdef ENABLE_AVX
#   ifdef _WIN32
#      include<intrin.h>
#   endif
#   include<immintrin.h>
#elif defined(__AVX2__)
	#include<immintrin.h>
#endif

void mat4x4_multi_vec4(const vec4x4_t lf_mat4,const float rf_vec4[4],float out_vec4[4]){/*TODO check if it's correct*/
	out_vec4[0] = lf_mat4[0][1] * rf_vec4[0] +
				  lf_mat4[0][1] * rf_vec4[1] +
				  lf_mat4[0][2] * rf_vec4[2] +
				  lf_mat4[0][3] * rf_vec4[3];

	out_vec4[1] = lf_mat4[1][0] * rf_vec4[0] +
				  lf_mat4[1][1] * rf_vec4[1] +
				  lf_mat4[1][2] * rf_vec4[2] +
				  lf_mat4[1][3] * rf_vec4[3];

	out_vec4[2] = lf_mat4[2][0] * rf_vec4[0] +
				  lf_mat4[2][1] * rf_vec4[1] +
				  lf_mat4[2][2] * rf_vec4[2] +
				  lf_mat4[2][3] * rf_vec4[3];

	out_vec4[3] = lf_mat4[3][0] * rf_vec4[0] +
				  lf_mat4[3][1] * rf_vec4[1] +
				  lf_mat4[3][2] * rf_vec4[2] +
				  lf_mat4[3][3] * rf_vec4[3];
}
/*
static inline __m128 lincomb_AVX_4mem(const float *a, const vec4x4_t B){
    __m128 result;
    result = _mm_mul_ps(_mm_broadcast_ss(&a[0]), (__m128)B[0]);
    result = _mm_add_ps(result, _mm_mul_ps(_mm_broadcast_ss(&a[1]), (__m128)B[1]));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_broadcast_ss(&a[2]), (__m128)B[2]));
    result = _mm_add_ps(result, _mm_mul_ps(_mm_broadcast_ss(&a[3]), (__m128)B[3]));
    return result;
}*/



void mat4x4_multi_mat4x4(const vec4x4_t mat,const vec4x4_t mat2, vec4x4_t outf_mat4){
    #if defined(ENABLE_AVX)
	int i;
	__m128 row1 = _mm_load_ps(mat2[0]);
	__m128 row2 = _mm_load_ps(mat2[1]);
	__m128 row3 = _mm_load_ps(mat2[2]);
	__m128 row4 = _mm_load_ps(mat2[3]);
	for(i = 0; i < 4; i++){
		__m128 brod1 = _mm_set1_ps(mat[i][0]);
		__m128 brod2 = _mm_set1_ps(mat[i][1]);
		__m128 brod3 = _mm_set1_ps(mat[i][2]);
		__m128 brod4 = _mm_set1_ps(mat[i][3]);
		__m128 row = _mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(brod1, row1),
						_mm_mul_ps(brod2,row2)),
						_mm_add_ps(
							_mm_mul_ps(brod3,row3),
							_mm_mul_ps(brod4,row4)));
		_mm_store_ps(outf_mat4[i],row);
		continue;
	}
#else
    float a00 = mat[0][0], a01 =  mat[0][1], a02 = mat[0][2], a03 = mat[0][3],
        a10 =    mat[1][0], a11 =  mat[1][1], a12 = mat[1][2], a13 = mat[1][3],
        a20 =    mat[2][0], a21 =  mat[2][1], a22 = mat[2][2], a23 = mat[2][3],
        a30 =    mat[3][0], a31 =  mat[3][1], a32 = mat[3][2], a33 = mat[3][3],

        b00 = mat2[0][0], b01 = mat2[0][1], b02 = mat2[0][2], b03 = mat2[0][3],
        b10 = mat2[1][0], b11 = mat2[1][1], b12 = mat2[1][2], b13 = mat2[1][3],
        b20 = mat2[2][0], b21 = mat2[2][1], b22 = mat2[2][2], b23 = mat2[2][3],
        b30 = mat2[3][0], b31 = mat2[3][1], b32 = mat2[3][2], b33 = mat2[3][3];

    outf_mat4[0][0] = b00 * a00 + b01 * a10 + b02 * a20 + b03 * a30;
    outf_mat4[0][1] = b00 * a01 + b01 * a11 + b02 * a21 + b03 * a31;
    outf_mat4[0][2] = b00 * a02 + b01 * a12 + b02 * a22 + b03 * a32;
    outf_mat4[0][3] = b00 * a03 + b01 * a13 + b02 * a23 + b03 * a33;

    outf_mat4[1][0] = b10 * a00 + b11 * a10 + b12 * a20 + b13 * a30;
    outf_mat4[1][1] = b10 * a01 + b11 * a11 + b12 * a21 + b13 * a31;
    outf_mat4[1][2] = b10 * a02 + b11 * a12 + b12 * a22 + b13 * a32;
    outf_mat4[1][3] = b10 * a03 + b11 * a13 + b12 * a23 + b13 * a33;

    outf_mat4[2][0] = b20 * a00 + b21 * a10 + b22 * a20 + b23 * a30;
    outf_mat4[2][1] = b20 * a01 + b21 * a11 + b22 * a21 + b23 * a31;
    outf_mat4[2][2] = b20 * a02 + b21 * a12 + b22 * a22 + b23 * a32;
    outf_mat4[2][3] = b20 * a03 + b21 * a13 + b22 * a23 + b23 * a33;

    outf_mat4[3][0] = b30 * a00 + b31 * a10 + b32 * a20 + b33 * a30;
    outf_mat4[3][1] = b30 * a01 + b31 * a11 + b32 * a21 + b33 * a31;
    outf_mat4[3][2] = b30 * a02 + b31 * a12 + b32 * a22 + b33 * a32;
    outf_mat4[3][3] = b30 * a03 + b31 * a13 + b32 * a23 + b33 * a33;


#endif
}

void mat4x4_divs_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4){
	// division.
	outf_mat4[0][0] = lf_mat4[0][0] / rf_mat4[0][0];	outf_mat4[0][1] = lf_mat4[0][1] / rf_mat4[0][1];	outf_mat4[0][2] = lf_mat4[0][2] / rf_mat4[0][2];	outf_mat4[0][3] = lf_mat4[0][3] / rf_mat4[0][3];
	outf_mat4[1][0] = lf_mat4[1][0] / rf_mat4[1][0];	outf_mat4[1][1] = lf_mat4[1][1] / rf_mat4[1][1];	outf_mat4[1][2] = lf_mat4[1][2] / rf_mat4[1][2];	outf_mat4[1][3] = lf_mat4[1][3] / rf_mat4[1][3];
	outf_mat4[2][0] = lf_mat4[2][0] / rf_mat4[2][0];	outf_mat4[2][1] = lf_mat4[2][1] / rf_mat4[2][1];	outf_mat4[2][2] = lf_mat4[2][2] / rf_mat4[2][2];	outf_mat4[2][3] = lf_mat4[2][3] / rf_mat4[2][3];
	outf_mat4[3][0] = lf_mat4[3][0] / rf_mat4[3][0];	outf_mat4[3][1] = lf_mat4[3][1] / rf_mat4[3][1];	outf_mat4[3][2] = lf_mat4[3][2] / rf_mat4[3][2];	outf_mat4[3][3] = lf_mat4[3][3] / rf_mat4[3][3];
}
void mat4x4_addi_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4){
	// addition
	outf_mat4[0][0] = lf_mat4[0][0] + rf_mat4[0][0];	outf_mat4[0][1] = lf_mat4[0][1] + rf_mat4[0][1];	outf_mat4[0][2] = lf_mat4[0][2] + rf_mat4[0][2];	outf_mat4[0][3] = lf_mat4[0][3] + rf_mat4[0][3];
	outf_mat4[1][0] = lf_mat4[1][0] + rf_mat4[1][0];	outf_mat4[1][1] = lf_mat4[1][1] + rf_mat4[1][1];	outf_mat4[1][2] = lf_mat4[1][2] + rf_mat4[1][2];	outf_mat4[1][3] = lf_mat4[1][3] + rf_mat4[1][3];
	outf_mat4[2][0] = lf_mat4[2][0] + rf_mat4[2][0];	outf_mat4[2][1] = lf_mat4[2][1] + rf_mat4[2][1];	outf_mat4[2][2] = lf_mat4[2][2] + rf_mat4[2][2];	outf_mat4[2][3] = lf_mat4[2][3] + rf_mat4[2][3];
	outf_mat4[3][0] = lf_mat4[3][0] + rf_mat4[3][0];	outf_mat4[3][1] = lf_mat4[3][1] + rf_mat4[3][1];	outf_mat4[3][2] = lf_mat4[3][2] + rf_mat4[3][2];	outf_mat4[3][3] = lf_mat4[3][3] + rf_mat4[3][3];
}
void mat4x4_subt_mat4x4(const vec4x4_t lf_mat4, const vec4x4_t rf_mat4, vec4x4_t outf_mat4){
	outf_mat4[0][0] = lf_mat4[0][0] - rf_mat4[0][0];	outf_mat4[0][1] = lf_mat4[0][1] - rf_mat4[0][1];	outf_mat4[0][2] = lf_mat4[0][2] - rf_mat4[0][2];	outf_mat4[0][3] = lf_mat4[0][3] - rf_mat4[0][3];
	outf_mat4[1][0] = lf_mat4[1][0] - rf_mat4[1][0];	outf_mat4[1][1] = lf_mat4[1][1] - rf_mat4[1][1];	outf_mat4[1][2] = lf_mat4[1][2] - rf_mat4[1][2];	outf_mat4[1][3] = lf_mat4[1][3] - rf_mat4[1][3];
	outf_mat4[2][0] = lf_mat4[2][0] - rf_mat4[2][0];	outf_mat4[2][1] = lf_mat4[2][1] - rf_mat4[2][1];	outf_mat4[2][2] = lf_mat4[2][2] - rf_mat4[2][2];	outf_mat4[2][3] = lf_mat4[2][3] - rf_mat4[2][3];
	outf_mat4[3][0] = lf_mat4[3][0] - rf_mat4[3][0];	outf_mat4[3][1] = lf_mat4[3][1] - rf_mat4[3][1];	outf_mat4[3][2] = lf_mat4[3][2] - rf_mat4[3][2];	outf_mat4[3][3] = lf_mat4[3][3] - rf_mat4[3][3];
}


void mat4x4_identity(vec4x4_t f_mat4){
	f_mat4[0][0] = 1.0f;f_mat4[1][0] = 0.0f;f_mat4[2][0] = 0.0f;f_mat4[3][0] = 0.0f;
	f_mat4[0][1] = 0.0f;f_mat4[1][1] = 1.0f;f_mat4[2][1] = 0.0f;f_mat4[3][1] = 0.0f;
	f_mat4[0][2] = 0.0f;f_mat4[1][2] = 0.0f;f_mat4[2][2] = 1.0f;f_mat4[3][2] = 0.0f;
	f_mat4[0][3] = 0.0f;f_mat4[1][3] = 0.0f;f_mat4[2][3] = 0.0f;f_mat4[3][3] = 1.0f;
}
void mat4x4_transpose(vec4x4_t f_mat4){
    // origional		transpose
	//|a b c d |	 |a e i m|
	//|e f g h |	 |b f j n|
	//|i j k l |	 |c g k o|
	//|m n o q |	 |d h l q|
	float temp;
	// b | c
	temp = f_mat4[1][0];            //e
	f_mat4[1][0] = f_mat4[0][1];    //b
	f_mat4[0][1] = temp;

	// c | i
	temp = f_mat4[2][0];
	f_mat4[2][0] = f_mat4[0][2];
	f_mat4[0][2] = temp;

	// m | d
	temp = f_mat4[3][0];
	f_mat4[3][0] = f_mat4[0][3];
	f_mat4[0][3] = temp;

	// h | n
	temp = f_mat4[1][3];
	f_mat4[1][3] = f_mat4[3][1];
	f_mat4[3][1] = temp;

	// h | n
	temp = f_mat4[1][3];
	f_mat4[1][3] = f_mat4[3][1];
	f_mat4[3][1] = temp;

	// l | o
	temp = f_mat4[2][3];
	f_mat4[2][3] = f_mat4[3][2];
	f_mat4[3][2] = temp;

	// g | j
	temp = f_mat4[2][1];
	f_mat4[2][1] = f_mat4[1][2];
	f_mat4[1][2] = temp;
}
float mat4x4_determinant(vec4x4_t f_mat4){
	return f_mat4[0][0]* f_mat4[1][1]* f_mat4[2][2]* f_mat4[3][3] - f_mat4[0][0]* f_mat4[1][1]* f_mat4[2][3]* f_mat4[3][2] + f_mat4[0][0]* f_mat4[1][2]* f_mat4[2][3]* f_mat4[3][1] -  f_mat4[0][0]* f_mat4[1][2]* f_mat4[2][1]* f_mat4[3][3]
		 + f_mat4[0][0]* f_mat4[1][3]* f_mat4[2][1]* f_mat4[3][2] - f_mat4[0][0]* f_mat4[1][3]* f_mat4[2][2]* f_mat4[3][1] - f_mat4[0][1]* f_mat4[1][2]* f_mat4[2][3]* f_mat4[3][0] +  f_mat4[0][1]* f_mat4[1][2]* f_mat4[2][0]* f_mat4[3][3]
		 - f_mat4[0][1]* f_mat4[1][3]* f_mat4[2][0]* f_mat4[3][2] + f_mat4[0][1]* f_mat4[1][3]* f_mat4[2][2]* f_mat4[3][0] - f_mat4[0][1]* f_mat4[1][0]* f_mat4[2][2]* f_mat4[3][3] +  f_mat4[0][1]* f_mat4[1][0]* f_mat4[2][3]* f_mat4[3][2]
		 + f_mat4[0][2]* f_mat4[1][3]* f_mat4[2][0]* f_mat4[3][1] - f_mat4[0][2]* f_mat4[1][3]* f_mat4[2][1]* f_mat4[3][0] + f_mat4[0][2]* f_mat4[1][0]* f_mat4[2][1]* f_mat4[3][3] -  f_mat4[0][2]* f_mat4[1][0]* f_mat4[2][3]* f_mat4[3][1]
		 + f_mat4[0][2]* f_mat4[1][1]* f_mat4[2][3]* f_mat4[3][0] - f_mat4[0][2]* f_mat4[1][1]* f_mat4[2][0]* f_mat4[3][3] - f_mat4[0][3]* f_mat4[1][0]* f_mat4[2][1]* f_mat4[3][2] +  f_mat4[0][3]* f_mat4[1][0]* f_mat4[2][2]* f_mat4[3][1]
		 - f_mat4[0][3]* f_mat4[1][1]* f_mat4[2][2]* f_mat4[3][0] + f_mat4[0][3]* f_mat4[1][1]* f_mat4[2][0]* f_mat4[3][2] - f_mat4[0][3]* f_mat4[1][2]* f_mat4[2][0]* f_mat4[3][1] +  f_mat4[0][3]* f_mat4[1][2]* f_mat4[2][1]* f_mat4[3][0];
}
float mat4x4_inverse(vec4x4_t f_mat4){   //TODO check if functional
    float detm;
	float invdet;
	float res[4][4];
	detm = determinant_mat4(f_mat4);
	if(detm > 0.0f){
		invdet = 1.0f / detm;
		res[0][0] = invdet  * (f_mat4[1][1] * (f_mat4[2][2] * f_mat4[3][3] - f_mat4[2][3] * f_mat4[3][2]) + f_mat4[1][2] * (f_mat4[2][3] * f_mat4[3][1] - f_mat4[2][1] * f_mat4[3][3]) + f_mat4[1][3] * (f_mat4[2][1] * f_mat4[3][2] - f_mat4[2][2] * f_mat4[3][1]));
		res[0][1] = -invdet * (f_mat4[0][1] * (f_mat4[2][2] * f_mat4[3][3] - f_mat4[2][3] * f_mat4[3][2]) + f_mat4[0][2] * (f_mat4[2][3] * f_mat4[3][1] - f_mat4[2][1] * f_mat4[3][3]) + f_mat4[0][3] * (f_mat4[2][1] * f_mat4[3][2] - f_mat4[2][2] * f_mat4[3][1]));
		res[0][2] = invdet  * (f_mat4[0][1] * (f_mat4[1][2] * f_mat4[3][3] - f_mat4[1][3] * f_mat4[3][2]) + f_mat4[0][2] * (f_mat4[1][3] * f_mat4[3][1] - f_mat4[1][1] * f_mat4[3][3]) + f_mat4[0][3] * (f_mat4[1][1] * f_mat4[3][2] - f_mat4[1][2] * f_mat4[3][1]));
		res[0][3] = -invdet * (f_mat4[0][1] * (f_mat4[1][2] * f_mat4[2][3] - f_mat4[1][3] * f_mat4[2][2]) + f_mat4[0][2] * (f_mat4[1][3] * f_mat4[2][1] - f_mat4[1][1] * f_mat4[2][3]) + f_mat4[0][3] * (f_mat4[1][1] * f_mat4[2][2] - f_mat4[1][2] * f_mat4[2][1]));
		res[1][0] = -invdet * (f_mat4[1][0] * (f_mat4[2][2] * f_mat4[3][3] - f_mat4[2][3] * f_mat4[3][2]) + f_mat4[1][2] * (f_mat4[2][3] * f_mat4[3][0] - f_mat4[2][0] * f_mat4[3][3]) + f_mat4[1][3] * (f_mat4[2][0] * f_mat4[3][2] - f_mat4[2][2] * f_mat4[3][0]));
		res[1][1] = invdet  * (f_mat4[0][0] * (f_mat4[2][2] * f_mat4[3][3] - f_mat4[2][3] * f_mat4[3][2]) + f_mat4[0][2] * (f_mat4[2][3] * f_mat4[3][0] - f_mat4[2][0] * f_mat4[3][3]) + f_mat4[0][3] * (f_mat4[2][0] * f_mat4[3][2] - f_mat4[2][2] * f_mat4[3][0]));
		res[1][2] = -invdet * (f_mat4[0][0] * (f_mat4[1][2] * f_mat4[3][3] - f_mat4[1][3] * f_mat4[3][2]) + f_mat4[0][2] * (f_mat4[1][3] * f_mat4[3][0] - f_mat4[1][0] * f_mat4[3][3]) + f_mat4[0][3] * (f_mat4[1][0] * f_mat4[3][2] - f_mat4[1][2] * f_mat4[3][0]));
		res[1][3] = invdet  * (f_mat4[0][0] * (f_mat4[1][2] * f_mat4[2][3] - f_mat4[1][3] * f_mat4[2][2]) + f_mat4[0][2] * (f_mat4[1][3] * f_mat4[2][0] - f_mat4[1][0] * f_mat4[2][3]) + f_mat4[0][3] * (f_mat4[1][0] * f_mat4[2][2] - f_mat4[1][2] * f_mat4[2][0]));
		res[2][0] = invdet  * (f_mat4[1][0] * (f_mat4[2][1] * f_mat4[3][3] - f_mat4[2][3] * f_mat4[3][1]) + f_mat4[1][1] * (f_mat4[2][3] * f_mat4[3][0] - f_mat4[2][0] * f_mat4[3][3]) + f_mat4[1][3] * (f_mat4[2][0] * f_mat4[3][1] - f_mat4[2][1] * f_mat4[3][0]));
		res[2][1] = -invdet * (f_mat4[0][0] * (f_mat4[2][1] * f_mat4[3][3] - f_mat4[2][3] * f_mat4[3][1]) + f_mat4[0][1] * (f_mat4[2][3] * f_mat4[3][0] - f_mat4[2][0] * f_mat4[3][3]) + f_mat4[0][3] * (f_mat4[2][0] * f_mat4[3][1] - f_mat4[2][1] * f_mat4[3][0]));
		res[2][2] = invdet  * (f_mat4[0][0] * (f_mat4[1][1] * f_mat4[3][3] - f_mat4[1][3] * f_mat4[3][1]) + f_mat4[0][1] * (f_mat4[1][3] * f_mat4[3][0] - f_mat4[1][0] * f_mat4[3][3]) + f_mat4[0][3] * (f_mat4[1][0] * f_mat4[3][1] - f_mat4[1][1] * f_mat4[3][0]));
		res[2][3] = -invdet * (f_mat4[0][0] * (f_mat4[1][1] * f_mat4[2][3] - f_mat4[1][3] * f_mat4[2][1]) + f_mat4[0][1] * (f_mat4[1][3] * f_mat4[2][0] - f_mat4[1][0] * f_mat4[2][3]) + f_mat4[0][3] * (f_mat4[1][0] * f_mat4[2][1] - f_mat4[1][1] * f_mat4[2][0]));
		res[3][0] = -invdet * (f_mat4[1][0] * (f_mat4[2][1] * f_mat4[3][2] - f_mat4[2][2] * f_mat4[3][1]) + f_mat4[1][1] * (f_mat4[2][2] * f_mat4[3][0] - f_mat4[2][0] * f_mat4[3][2]) + f_mat4[1][2] * (f_mat4[2][0] * f_mat4[3][1] - f_mat4[2][1] * f_mat4[3][0]));
		res[3][1] = invdet  * (f_mat4[0][0] * (f_mat4[2][1] * f_mat4[3][2] - f_mat4[2][2] * f_mat4[3][1]) + f_mat4[0][1] * (f_mat4[2][2] * f_mat4[3][0] - f_mat4[2][0] * f_mat4[3][2]) + f_mat4[0][2] * (f_mat4[2][0] * f_mat4[3][1] - f_mat4[2][1] * f_mat4[3][0]));
		res[3][2] = -invdet * (f_mat4[0][0] * (f_mat4[1][1] * f_mat4[3][2] - f_mat4[1][2] * f_mat4[3][1]) + f_mat4[0][1] * (f_mat4[1][2] * f_mat4[3][0] - f_mat4[1][0] * f_mat4[3][2]) + f_mat4[0][2] * (f_mat4[1][0] * f_mat4[3][1] - f_mat4[1][1] * f_mat4[3][0]));
		res[3][3] = invdet  * (f_mat4[0][0] * (f_mat4[1][1] * f_mat4[2][2] - f_mat4[1][2] * f_mat4[2][1]) + f_mat4[0][1] * (f_mat4[1][2] * f_mat4[2][0] - f_mat4[1][0] * f_mat4[2][2]) + f_mat4[0][2] * (f_mat4[1][0] * f_mat4[2][1] - f_mat4[1][1] * f_mat4[2][0]));
		memcpy(f_mat4,res,sizeof(res));

		return 1.0f / detm;

	}
    return 0.0f;

}


void mat4x4_translation(vec4x4_t f_mat4,float x, float y, float z){
	//translation
	f_mat4[0][0] = 1.0f;f_mat4[1][0] = 0.0f;f_mat4[2][0] = 0.0f;f_mat4[3][0] = x;
	f_mat4[0][1] = 0.0f;f_mat4[1][1] = 1.0f;f_mat4[2][1] = 0.0f;f_mat4[3][1] = y;
	f_mat4[0][2] = 0.0f;f_mat4[1][2] = 0.0f;f_mat4[2][2] = 1.0f;f_mat4[3][2] = z;
	f_mat4[0][3] = 0.0f;f_mat4[1][3] = 0.0f;f_mat4[2][3] = 0.0f;f_mat4[3][3] = 1.0f;
}
void mat4x4_translationv(vec4x4_t f_mat4,const vec3_t translation){
	//translation
	f_mat4[0][0] = 1.0f;f_mat4[1][0] = 0.0f;f_mat4[2][0] = 0.0f;f_mat4[3][0] = translation[0];
	f_mat4[0][1] = 0.0f;f_mat4[1][1] = 1.0f;f_mat4[2][1] = 0.0f;f_mat4[3][1] = translation[1];
	f_mat4[0][2] = 0.0f;f_mat4[1][2] = 0.0f;f_mat4[2][2] = 1.0f;f_mat4[3][2] = translation[2];
	f_mat4[0][3] = 0.0f;f_mat4[1][3] = 0.0f;f_mat4[2][3] = 0.0f;f_mat4[3][3] = 1.0f;
}


/**
*/
void mat4x4_scale(vec4x4_t f_mat4, float x,float y, float z){
	//scaling
	f_mat4[0][0] = x;       f_mat4[0][1] = 0.0f;	f_mat4[0][2] = 0.0f;	f_mat4[0][3] = 0.0f;
	f_mat4[1][0] = 0.0f;	f_mat4[1][1] = y;       f_mat4[1][2] = 0.0f;	f_mat4[1][3] = 0.0f;
	f_mat4[2][0] = 0.0f;	f_mat4[2][1] = 0.0f;	f_mat4[2][2] = x;       f_mat4[2][3] = 0.0f;
	f_mat4[3][0] = 0.0f;	f_mat4[3][1] = 0.0f;	f_mat4[3][2] = 0.0f;	f_mat4[3][3] = 1.0f;
}
void mat4x4_scalev(vec4x4_t f_mat4, vec3_t scale){
	//scaling
	f_mat4[0][0] = scale[0];f_mat4[0][1] = 0.0f;	f_mat4[0][2] = 0.0f;	f_mat4[0][3] = 0.0f;
	f_mat4[1][0] = 0.0f;	f_mat4[1][1] = scale[1];f_mat4[1][2] = 0.0f;	f_mat4[1][3] = 0.0f;
	f_mat4[2][0] = 0.0f;	f_mat4[2][1] = 0.0f;	f_mat4[2][2] = scale[2];f_mat4[2][3] = 0.0f;
	f_mat4[3][0] = 0.0f;	f_mat4[3][1] = 0.0f;	f_mat4[3][2] = 0.0f;	f_mat4[3][3] = 1.0f;
}


void mat4x4_rotation(vec4x4_t f_mat4,float angle,const vec3_t axis){



}
void mat4x4_rotationX(vec4x4_t f_mat4, float x_radi){
	// rotation X in eular
	f_mat4[0][0] = 1.0f;f_mat4[0][1] = 0.0f;		f_mat4[0][2] = 0.0f;			f_mat4[0][3] = 0.0f;
	f_mat4[1][0] = 0.0f;f_mat4[1][1] = cosf(x_radi);f_mat4[1][2] = -sinf(x_radi);	f_mat4[1][3] = 0.0f;
	f_mat4[2][0] = 0.0f;f_mat4[2][1] = sinf(x_radi);f_mat4[2][2] = cosf(x_radi);	f_mat4[2][3] = 0.0f;
	f_mat4[3][0] = 0.0f;f_mat4[3][1] = 0.0f;		f_mat4[3][2] = 0.0f;			f_mat4[3][3] = 1.0f;
}
void mat4x4_rotationY(vec4x4_t f_mat4, float y_radi){
	// rotation Y in eular
	f_mat4[0][0] = cosf(y_radi);	f_mat4[0][1] = 0.0f; f_mat4[0][2] = -sinf(y_radi);f_mat4[0][3] = 0.0f;
	f_mat4[1][0] = 0.0f;			f_mat4[1][1] = 1.0f; f_mat4[1][2] = 0.0f;		  f_mat4[1][3] = 0.0f;
	f_mat4[2][0] = sinf(y_radi);	f_mat4[2][1] = 0.0f; f_mat4[2][2] = cosf(y_radi); f_mat4[2][3] = 0.0f;
	f_mat4[3][0] = 0.0f;			f_mat4[3][1] = 0.0f; f_mat4[3][2] = 0.0f;		  f_mat4[3][3] = 1.0f;
}
void mat4x4_rotationZ(vec4x4_t f_mat4, float z_radi){
	// rotation Z in eular
	f_mat4[0][0] = cosf(z_radi);	f_mat4[0][1] = -sinf(z_radi); f_mat4[0][2] = 0.0f; f_mat4[0][3] = 0.0f;
	f_mat4[1][0] = sinf(z_radi); f_mat4[1][1] = cosf(z_radi); f_mat4[1][2] = 0.0f; f_mat4[1][3] = 0.0f;
	f_mat4[2][0] = 0.0f;		 f_mat4[2][1] = 0.0f;		  f_mat4[2][2] = 1.0f; f_mat4[2][3] = 0.0f;
	f_mat4[3][0] = 0.0f;		 f_mat4[3][1] = 0.0f;		  f_mat4[3][2] = 0.0f; f_mat4[3][3] = 1.0f;
}


void mat4x4_multi_translation(vec4x4_t f_mat4,const vec3_t translate){
	vec4x4 ftranslate;
	vec4x4 ftranslate2;
	translation_mat4(ftranslate, translate);
	mulit_mat4(f_mat4,ftranslate,ftranslate2);
	memcpy(f_mat4,ftranslate2,sizeof(vec_t) * 16);
}
void mat4x4_multi_scale(vec4x4_t f_mat4,const vec3_t scale){
	vec4x4 fscale;
	vec4x4 fscale2;
	scale_mat4(fscale, scale);
	mulit_mat4(f_mat4,fscale,fscale2);
	memcpy(f_mat4,fscale2, sizeof(float) * 16);
}
void mat4x4_multi_rotationx(vec4x4_t f_mat4, float f_x_radi){
	vec4x4 f_rot_x;
	vec4x4 f_rot_x2;
	rotationX_mat4(f_rot_x, f_x_radi);
	mulit_mat4(f_mat4,f_rot_x,f_rot_x2);
	memcpy(f_mat4,f_rot_x2,sizeof(vec4x4));
}
void mat4x4_multi_rotationy(vec4x4_t f_mat4, float f_y_radi){
	vec4x4 f_rot_y;
	rotationY_mat4(f_rot_y, f_y_radi);
	mulit_mat4(f_mat4,f_rot_y,f_mat4);
}
void mat4x4_multi_rotationz(vec4x4_t f_mat4, float f_z_radi){
	vec4x4 f_rot_z,f_rot_z2;
	rotationZ_mat4(f_rot_z, f_z_radi);
	mulit_mat4(f_mat4,f_rot_z,f_rot_z2);
	memcpy(f_mat4,f_rot_z2,sizeof(vec4x4));
}

void mat4x4_multi_rotationQ(vec4x4_t f_mat4,const float f_quad[4]){
	vec4x4 f_rot_q;
	vec4x4 f_rot_q2;
	rotationQ_mat4(f_rot_q, f_quad);
	mulit_mat4(f_mat4,f_rot_q,f_rot_q2);
	memcpy(f_mat4,f_rot_q2,sizeof(vec4x4));
}


void mat4x4_proj(vec4x4_t f_mat4, float f_fov, float f_aspect, float f_near, float f_far){

    f_mat4[0][0] = 1.0f / (tanf(DEG2RAD(f_fov * 0.5f)) * f_aspect);
    f_mat4[1][0] = 0.0f;
    f_mat4[2][0] = 0.0f;
    f_mat4[3][0] = 0.0f;

    f_mat4[0][1] = 0.0f;
    f_mat4[1][1] = 1.0f / tanf(DEG2RAD(f_fov * 0.5f));
    f_mat4[2][1] = 0.0f;
    f_mat4[3][1] = 0.0f;

    f_mat4[0][2] = 0.0f;
    f_mat4[1][2] = 0.0f;
    f_mat4[2][2] = (f_far + f_near) / (f_near - f_far);
    f_mat4[3][2] = (2.0f * f_far * f_near) / (f_near - f_far);

    f_mat4[0][3] = 0.0f;
    f_mat4[1][3] = 0.0f;
    f_mat4[2][3] = -1.0f;
    f_mat4[3][3] = 0.0f;
}

void mat4x4_orth(vec4x4_t f_mat4,float f_right, float f_left, float f_top, float f_bottom, float f_far,float f_near){
    f_mat4[0][0] = 2.0f/(f_right - f_left);
    f_mat4[1][0] = 0.0f;
    f_mat4[2][0] = 0.0f;
    f_mat4[3][0] = -(f_right + f_left)/(f_right - f_left);

    f_mat4[0][1] = 0.0f;
    f_mat4[1][1] = 2.0f/(f_top - f_bottom);
    f_mat4[2][1] = 0.0f;
    f_mat4[3][1] = -(f_top + f_bottom)/(f_top - f_bottom);

    f_mat4[0][1] = 0.0f;
    f_mat4[1][1] = 0.0f;
    f_mat4[2][1] = -2.0f/(f_far - f_near);
    f_mat4[3][1] = -(f_far + f_near)/(f_far - f_near);

    f_mat4[0][3] = 0.0f;
    f_mat4[1][3] = 0.0f;
    f_mat4[2][3] = 0.0f;
    f_mat4[3][3] = 1.0f;
}
int mat4x4_unproj(float winx, float winy, float winz,const vec4x4_t projection,const vec4x4_t modelview,const int* viewport,vec3_t pos){
	vec4x4_t mvp;
	vec4x4_t m;
    mat4x4_multi_mat4x4(projection, modelview,mvp);
    mat4x4_inverse(mvp);

}

