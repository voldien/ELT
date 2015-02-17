#include"EngineConfig.h"
#include"EngineAssembly.h"
#include<signal.h>
#include<string.h>

#ifdef EX_WINDOWS		// TODO solve
#   include"System/Win32/wnd_common.h"
#   include<GL/gl.h>
#elif defined(EX_LINUX)     /** Linux   */
#   include"System/Unix/unix_win.h"
#   include<GL/gl.h>
#elif defined(EX_ANDROID)   /** Android */
	#ifdef GL_ES_VERSION_2_0
        #include<GLES/gl2.h>
        #include<GLES/gl2ext.h>
        #include<GLES/gl2platform.h>
    #elif defined(GL_ES_VERSION_1_0)
        #include<GLES/gl.h>
        #include<GLES/glext.h>
        #include<GLES/glplatform.h>
	#endif
#endif

#include"System/elt_gl.h"
#include"System/elt_cl.h"




#ifdef EX_WINDOWS
#	include<GL/glext.h>
#elif defined(EX_LINUX)
#endif

EngineDescription engineDescription = {0};

DECLSPEC const Uint64 ELTAPIENTRY ExGetEngineFlag(void){	return engineDescription.EngineFlag;}
DECLSPEC ExBoolean ELTAPIENTRY ExIsEngineState(const ULLong engineBitState){ return (engineDescription.EngineFlag & engineBitState) != 0 ? TRUE : FALSE;}
DECLSPEC EngineDescription ELTAPIENTRY ExGetEngineDescription(void){return engineDescription;}
DECLSPEC EngineDescription* ELTAPIENTRY ExGetEngineDescriptionPointer(void){return ((EngineDescription*)&engineDescription);}

/**
    \Hint on how stuff will be implemented.
*/
extern DECLSPEC void ELTAPIENTRY ExSetHint(Enum e_enum, int value){
    switch(e_enum){
#ifdef __gl_h_
        case GL_DEPTH_BITS: engineDescription.DepthBits = value;break;
        case GL_STENCIL_BITS:engineDescription.StencilBits = value;break;
        case GL_ALPHA:engineDescription.alphaChannel = value;break;
        case GL_SAMPLES:engineDescription.sample[0] = CLAMP(value,0,UCHAR_MAX);break;
#endif

        default:break;
    }
}
/**
    \Hint
*/
extern DECLSPEC int ELTAPIENTRY ExGetHint(Enum e_enum){
    switch(e_enum){
#ifdef __gl_h_
        case GL_DEPTH_BITS: return engineDescription.DepthBits;
        case GL_STENCIL_BITS: return engineDescription.StencilBits;
        case GL_ALPHA:return engineDescription.alphaChannel;
        //case GL_SAMPLES:return engineDescription.sample[0];
#endif
        default:return 0;
    }
}

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
        case 0:break;
        default:break;
    }
    return 1;
}

static EngineDescription ELTAPIENTRY EngineDefaultDescription(void){
	EngineDescription defaultDescripton = {0};
	defaultDescripton.EngineFlag = 0;
	defaultDescripton.PixelType = (Uint)(ENGINE_RGBA | ENGINE_ALPHA);
	defaultDescripton.SampleQuality = 0;// sample buffer
	defaultDescripton.BufferCount = 1;
	defaultDescripton.BufferFlag = 1;
	defaultDescripton.AffinityCount = 1;
	defaultDescripton.nVersion = EX_ENGINE_VERSION;
	defaultDescripton.DepthBits = 24;
	defaultDescripton.ColorBits = 32;
	defaultDescripton.StencilBits = 8;
	defaultDescripton.AccumBits = 0;
	return defaultDescripton;
}
static EngineDescription ELTAPIENTRY EngineDirectXDescription(void){

	EngineDescription _description;
	memset(&_description,0, sizeof(EngineDescription));
	_description.EngineFlag = 0;
	_description.nVersion = EX_ENGINE_VERSION;
	_description.PixelType = (Uint)(ENGINE_RGB | ENGINE_ALPHA);

	_description.BufferCount = 1;
	_description.AffinityCount = 1;

	_description.DepthBits = 24;
	_description.ColorBits = 32;
	_description.AccumBits = 8;
	_description.StencilBits = 8;

	return _description;
}
static EngineDescription ELTAPIENTRY EngineOpenGLDescription(void){

	EngineDescription defaultDescripton;
	memset(&defaultDescripton,0, sizeof(EngineDescription));
	defaultDescripton.nVersion = EX_ENGINE_VERSION;
	defaultDescripton.EngineFlag = 0;
	defaultDescripton.PixelType = (Uint)(ENGINE_RGB | ENGINE_ALPHA);

	defaultDescripton.BufferCount = 1;
	defaultDescripton.AffinityCount = 1;

	defaultDescripton.DepthBits = 24;
	defaultDescripton.ColorBits = 32;
	defaultDescripton.AccumBits = 0;
	defaultDescripton.StencilBits = 8;

	return defaultDescripton;
}

