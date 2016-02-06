#ifndef _ELT_SAMPLES_COMMON_H_
#define _ELT_SAMPLES_COMMON_H_  1
#include"./../../include/EngineExAPI.h"
#include"./../../include/math/matrix.h"

#ifdef __cplusplus 
extern "C"{
#endif

typedef struct camera_controller{
	vec3_t position;
	quad_t rotation;
	vec3_t direction;
	vec4x4_t proj;
}CameraController ;


DECLSPEC extern void* ExCreateCharacterController(const vec3_t position);


DECLSPEC extern void ExUpdateCharacterController(CameraController* charactercontroller);


DECLSPEC extern void readArgument(int argc, char** argv);




#ifdef __cplusplus
}
#endif 


#endif 
