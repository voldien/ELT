#include"system/elt_gl.h"
#include"system.h"

#include "ppapi/c/pp_errors.h"
#include "ppapi/c/pp_module.h"
#include "ppapi/c/pp_var.h"
#include "ppapi/c/ppb.h"
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppb_messaging.h"
#include "ppapi/c/ppb_var.h"
#include "ppapi/c/ppp.h"
#include "ppapi/c/ppp_instance.h"
#include "ppapi/c/ppp_messaging.h"
#include "ppapi/c/pp_completion_callback.h"
#include "ppapi/c/ppb_graphics_3d.h"
#include "ppapi/gles2/gl2ext_ppapi.h"
#include "GLES2/gl2.h"

extern PPB_Instance* ppb_instance_interface;
extern PPB_GetInterface browser;


PP_Module module_id = 0;
PPB_Messaging* messaging_interface = NULL;
PPB_Var* var_interface = NULL;
PPB_Graphics3D* graphics3d_interface = NULL;
PP_Resource glContext = NULL;

void swap_callback(void* user_data, int32_t result){
  printf("swap result: %d\n", result);
}


ExOpenGLContext ExCreateGLContext(ExWin window, ExOpenGLContext shared){
	unsigned int width;
	unsigned int height;
	PP_Instance instance = ppb_instance_interface;

	ExPrintf("create opengl\n");

	if(!browser){
		ExPrintf("browser null\n");
		//ExDelay(1000);
	}

	if (!glInitializePPAPI(browser)) {
		ExPrintf("glInitializePPAPI failed\n");
	    return PP_ERROR_FAILED;
	}



	int32_t attribs[] = {PP_GRAPHICS3DATTRIB_WIDTH, 800,
					   PP_GRAPHICS3DATTRIB_HEIGHT, 600,
					   PP_GRAPHICS3DATTRIB_NONE};
	glContext = graphics3d_interface->Create(instance, shared, attribs);
	if (glContext == 0) {
			ExPrintf("failed to create graphics3d context\n");
		return PP_FALSE;
	}

	glSetCurrentContextPPAPI(glContext);

	if (!ppb_instance_interface->BindGraphics(instance, glContext)) {
		ExPrintf("failed to bind graphics3d context\n");
		return PP_FALSE;
	}

	glClearColor(0.1f, 0.9f, 0.4f, 0.9f);
	glClear(GL_COLOR_BUFFER_BIT);


	ExSwapBuffers(0);
	return glContext;
}

ExBoolean ExDestroyGLContext(ExWindowContext drawable, ExOpenGLContext glc){

	return 0;
}

void ExSwapBuffers(void* surface){
	struct PP_CompletionCallback callback = { swap_callback, NULL, PP_COMPLETIONCALLBACK_FLAG_NONE };
	int32_t ret = graphics3d_interface->SwapBuffers(glContext, callback);
	if (ret != PP_OK && ret != PP_OK_COMPLETIONPENDING) {
		printf("SwapBuffers failed with code %d\n", ret);
		return ;
	}
}

