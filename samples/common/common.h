#ifndef _ELT_SAMPLES_COMMON_H_
#define _ELT_SAMPLES_COMMON_H_  1
#include"./../../include/EngineExAPI.h"
#include"./../../include/math/matrix.h"

#ifdef __cplusplus 
extern "C"{
#endif

typedef struct camera_controller{
	exvec3f_t position;
	quad_t rotation;
	exvec3f_t direction;
	exvec4x4_t proj;
}CameraController;


/**/
extern void readArgument(int argc, char** argv);


extern void* ExCreateCharacterController(const exvec3f_t position);


extern void ExUpdateCharacterController(CameraController* charactercontroller);







#ifdef __cplusplus
}
#endif 


#endif 
