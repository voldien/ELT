#include"system/elt_gl.h"

#include <GLES2/gl2.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>



#include"ppapi/gles2/gl2ext_ppapi.h"
#include "ppapi/lib/gl/gles2/gl2ext_ppapi.h"

#include "ppapi/c/ppb.h"
#include "ppapi/c/pp_errors.h"





DECLSPEC OpenGLContext ELTAPIENTRY ExCreateGLContext(ExWin window){
	unsigned int width;
	unsigned int height;
	OpenGLContext glc;
	PPB_GetInterface inter;

	ExGetWindowSizev(window,&width);
	/*TEMP*/
	width = 800;
	height = 600;

	if(!glInitializePPAPI(inter)){
		fprintf(stderr,"failed to initalize PAPI");
		return NULL;
	}

	/*
    const int32_t attrib_list[] = {
      PP_GRAPHICS3DATTRIB_ALPHA_SIZE, 8,
      PP_GRAPHICS3DATTRIB_DEPTH_SIZE, 24,
      PP_GRAPHICS3DATTRIB_WIDTH, width,
      PP_GRAPHICS3DATTRIB_HEIGHT, height,
      PP_GRAPHICS3DATTRIB_NONE
    };*/

	glc = glGetInterfacePPAPI();

    if (!BindGraphics(glc)) {

    }

    glSetCurrentContextPPAPI(glc);



	return glc;
}


