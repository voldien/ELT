#include"EngineAssembly.h"
#include<signal.h>
#include<string.h>

#ifdef EX_WINDOWS		// TODO solve
	#pragma warning(disable : 4480) // enum
	#pragma warning(disable : 4995) // deprecated
#   include"system/win/wnd_common.h"
#   include<GL/gl.h>
#elif defined(EX_LINUX)     /** Linux   */
#   include"system/unix/unix_win.h"
#   include<GL/gl.h>
#elif defined(EX_ANDROID)   /** Android */

	#ifdef GL_ES_VERSION_3_0
		#include<GLES3/gl3.h>
		#include<GLES3/gl3ext.h>
		#include<GLES3/gl3platform.h>
	#elif defined(GL_ES_VERSION_2_0)
		#include<GLES2/gl2.h>
		//#include<GLES2/gl2ext.h>
		//#include<GLES2/gl2platform.h>
	#elif defined(GL_ES_VERSION_1_0)
		#include<GLES/gl.h>
		#include<GLES/glext.h>
		#include<GLES/glplatform.h>
	#endif
#endif

#include"system/elt_gl.h"
#include"system/elt_cl.h"


#ifdef EX_WINDOWS
#	include<GL/glext.h>
#elif defined(EX_LINUX)
#endif


#define ELT_DISPLAY 0x1
#define ELT_DISPLAY1 0x1
#define ELT_DISPLAY2 0x1
#define ELT_DISPLAY3 0x1
#define ELT_DISPLAY4 0x1

DECLSPEC int ELTAPIENTRY ExSetParameteri(Enum eflag, int value){
    switch(eflag){

        case 0:break;
#if defined(EX_WINDOWS)

#elif defined(EX_LINUX)
        case ELT_DISPLAY:display = value;break;
#endif
        default:break;
    }

    return 1;
}
DECLSPEC int ELTAPIENTRY ExSetParameterf(Enum eflag, float value){
    switch(eflag){
        case 0:
            break;
        default:
            break;
    }
    return 1;
}




