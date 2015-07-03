#include<string.h>
#include <stdlib.h>
#include <string.h>
#include "ppapi/c/pp_errors.h"
#include "ppapi/c/ppp.h"
// Include the interface headers.
// PPB APIs describe calls from the module to the browser.
// PPP APIs describe calls from the browser to the functions defined in your module.
#include "ppapi/c/ppb_instance.h"
#include "ppapi/c/ppp_instance.h"
#include "ppapi/c/ppb_input_event.h"
#include "ppapi/c/ppp_input_event.h"



extern int main(int argc, char** argv);

static PPB_Instance* ppb_instance_interface = NULL;
static PPB_InputEvent* ppb_input_event_interface = NULL;


static PP_Bool Instance_DidCreate(PP_Instance instance,
                                  uint32_t argc,
                                  const char* argn[],
                                  const char* argv[]) {
	return main(argc, argv);
	return PP_TRUE;
}

static PP_Bool Instance_HandleDocumentLoad(PP_Instance instance,
                                           PP_Resource url_loader) {
  /* NaCl modules do not need to handle the document load function. */
  return PP_FALSE;
}


// Define PPP_InitializeModule, the entry point of your module.
// Retrieve the API for the browser-side (PPB) interfaces you will use.
PP_EXPORT int32_t PPP_InitializeModule(PP_Module a_module_id, PPB_GetInterface get_browser) {
        ppb_instance_interface = (PPB_Instance*)(get_browser(PPB_INSTANCE_INTERFACE));
        ppb_input_event_interface = (PPB_InputEvent*)(get_browser(PPB_INPUT_EVENT_INTERFACE));

        return PP_OK;
}


PP_EXPORT const void* PPP_GetInterface(const char* interface_name) {
  if (strcmp(interface_name, PPP_INSTANCE_INTERFACE) == 0) {
	  static PPP_Instance instance_interface = {
      &Instance_DidCreate,
	  NULL,
	  NULL,
	  NULL,
      NULL,
    };

	  printf("desu");
	  /*
	  static PPP_Instance instance_interface = {
      &Instance_DidCreate,
      &Instance_DidDestroy,
      &Instance_DidChangeView,
      &Instance_DidChangeFocus,
      &Instance_HandleDocumentLoad,
    };
	*/


    return &instance_interface;
  }
  return NULL;
}


PP_EXPORT void PPP_ShutdownModule() {

}
