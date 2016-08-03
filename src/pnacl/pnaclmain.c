#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include"system.h"

#include<ppapi/c/ppb.h>
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
#include"ppapi/c/dev/ppb_truetype_font_dev.h"



extern int main(int argc, char** argv);

extern PP_Module module_id;
extern PPB_Messaging* messaging_interface;
extern PPB_Var* var_interface;
extern PPB_Graphics3D* graphics3d_interface;
extern PPB_Instance* instance_interface ;


PPB_Instance* instance_interface = NULL;
PPB_Instance* ppb_instance_interface = NULL;
PPB_GetInterface browser = NULL;
//PPB_InputEvent* ppb_input_event_interface = NULL;


static PP_Bool Instance_DidCreate(PP_Instance instance,
                                  uint32_t argc,
                                  const char* argn[],
                                  const char* argv[]) {
	printf("entered Instance_DidCreate\n");


	return (main(argc, argv) == EXIT_SUCCESS) ? PP_TRUE : PP_FALSE;
}
static void Instance_DidDestroy(PP_Instance instance) {

}

static void Instance_DidChangeView(PP_Instance instance,
                                   const struct PP_Rect* position,
                                   const struct PP_Rect* clip) {

}

static void Instance_DidChangeFocus(PP_Instance instance,
                                    PP_Bool has_focus) {
}

static PP_Bool Instance_HandleDocumentLoad(PP_Instance instance,
                                           PP_Resource url_loader) {
  return PP_FALSE;
}

void Messaging_HandleMessage(PP_Instance instance, struct PP_Var var_message) {
}


// Define PPP_InitializeModule, the entry point of your module.
// Retrieve the API for the browser-side (PPB) interfaces you will use.
PP_EXPORT int32_t PPP_InitializeModule(PP_Module a_module_id, PPB_GetInterface get_browser) {
	printf("entering initialize");
	if(!get_browser){
		printf("bad, browser null\n");
	}
	browser = get_browser;
	ppb_instance_interface = (PPB_Instance*)(get_browser(PPB_INSTANCE_INTERFACE));
	//ppb_input_event_interface = (PPB_InputEvent*)(get_browser(PPB_INPUT_EVENT_INTERFACE));

	module_id = a_module_id;
	var_interface = (struct PPB_Var*)(get_browser(PPB_VAR_INTERFACE));
	messaging_interface =
	  (struct PPB_Messaging*)(get_browser(PPB_MESSAGING_INTERFACE));
	graphics3d_interface =
	  (struct PPB_Graphics3D*)(get_browser(PPB_GRAPHICS_3D_INTERFACE));
	instance_interface =
	  (struct PPB_Instance*)(get_browser(PPB_INSTANCE_INTERFACE));


	if (!glInitializePPAPI(get_browser)) {
	    printf("glInitializePPAPI failed\n");
	    return PP_ERROR_FAILED;
	}else{
		printf("glInit success");
	}

	return PP_OK;
}


PP_EXPORT const void* PPP_GetInterface(const char* interface_name) {
	if (strcmp(interface_name, PPP_INSTANCE_INTERFACE) == 0) {
	    static PPP_Instance instance_interface = {
	      &Instance_DidCreate,
	      &Instance_DidDestroy,
	      &Instance_DidChangeView,
	      &Instance_DidChangeFocus,
	      &Instance_HandleDocumentLoad
	    };
	    return &instance_interface;
	  } else if (strcmp(interface_name, PPP_MESSAGING_INTERFACE) == 0) {
	    static PPP_Messaging messaging_interface = {
	      &Messaging_HandleMessage
	    };
	    return &messaging_interface;
	  }
	  return NULL;
}


PP_EXPORT void PPP_ShutdownModule() {
	ExPrintf("Shutting down module.\n");
}
