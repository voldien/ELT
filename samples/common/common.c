#include"common.c"



void ExUpdateCharacterController(CameraController* charactercontroller){
	vec3_t motion = {0};
	vec3_t dir;
	vec3_t right;
	vec3_t const rightdir = {1,0,0};
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
