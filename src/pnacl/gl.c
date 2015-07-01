#include"system/elt_gl.h"
#include"ppapi/gles2/gl2ext_ppapi.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/pp_errors.h"





DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	OpenGLContext glc;
   PPB_GetInterface inter;

	if(!glInitializePPAPI(inter)){
		return NULL;
	}

	glc = glGetInterfacePPAPI();


	return glc;
}


