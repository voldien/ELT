#include"common.h"

void readArgument(int argc, char** argv){

}

void ExUpdateCharacterController(CameraController* charactercontroller){
	exvec3f_t motion = {0};
	exvec3f_t dir;
	exvec3f_t right;
	exvec3f_t const rightdir = {1,0,0};
	quad_direction(charactercontroller->rotation, dir);
	quad_directionv(charactercontroller->rotation, rightdir, right);

	if(ExIsKeyDown(EXK_w)){
		VectorScale(motion,1,dir);
	}
	if(ExIsKeyDown(EXK_s)){
		VectorScale(motion,1,dir);
	}


	if(ExIsKeyDown(EXK_d)){
		VectorScale(motion,1,right);
	}
	if(ExIsKeyDown(EXK_a)){
		VectorScale(motion,-1,right);
	}

}
