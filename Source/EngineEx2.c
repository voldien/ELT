#include"EngineConfig.h"
#include"EngineAssembly.h"
#ifdef EX_WINDOWS		// TODO solve
#   include"System/Win32/wnd_common.h"
#elif defined(EX_LINUX)
#endif
#ifndef CMD_LIB_H
#   include<Cmd/cmdlib.h>
#endif
#include<GL/gl.h>
EngineDescription engineDescription = {0};

DECLSPEC void ELTAPIENTRY AssignDescription(const EngineDescription* p_engineDescription){memcpy(&engineDescription, p_engineDescription,sizeof(EngineDescription));}
DECLSPEC const Uint64 ELTAPIENTRY ExGetEngineFlag(void){	return engineDescription.EngineFlag;}
DECLSPEC Boolean ELTAPIENTRY ExIsEngineState(const ULLong engineBitState){ return (engineDescription.EngineFlag & engineBitState) != 0 ? TRUE : FALSE;}
DECLSPEC EngineDescription ELTAPIENTRY ExGetEngineDescription(void){return engineDescription;}
DECLSPEC EngineDescription* ELTAPIENTRY ExGetEngineDescriptionPointer(void){return ((EngineDescription*)&engineDescription);}

/**
    \Hint on how stuff will be implemented.
*/
extern DECLSPEC void ELTAPIENTRY ExSetHint(Enum e_enum, int value){
    switch(e_enum){
        case GL_DEPTH_BITS: engineDescription.DepthBits = value;break;
        case GL_STENCIL_BITS:engineDescription.StencilBits = value;break;
        case GL_ALPHA:engineDescription.alphaChannel = value;break;
        case GL_SAMPLES:engineDescription.sample[0] = CLAMP(value,0,UCHAR_MAX);break;
        //case GL_SAMPLES:engineDescription.sample[0] = CLAMP(value,0,5);break;
        default:break;
    }
}
/**
    \Hint
*/
extern DECLSPEC int ELTAPIENTRY ExGetHint(Enum e_enum){
    switch(e_enum){
        default:return 0;
    }
}

static EngineDescription ELTAPIENTRY EngineDefaultDescription(void){
	//DEVMODE _displayMode;
	//memset(&_displayMode, 0, sizeof(_displayMode));
	//EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &_displayMode);
	EngineDescription defaultDescripton = {0};
	defaultDescripton.EngineFlag = (
		//ENGINE_WINDOW |
		//ENGINE_SUPPORT_INPUT |
		ENGINE_SUPPORT_DOUBLEBUFFER |
		EX_OPENGL |
		ENGINE_SUPPORT_EXTENSION |
		ENGINE_SUPPORT_INPUT_FOREGROUND);
	defaultDescripton.PixelType = (Uint)(ENGINE_RGBA | ENGINE_ALPHA);
	//defaultDescripton.FullScreen_Hz = _displayMode.dmDisplayFrequency;
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
	//DEVMODE _displayMode;
	//memset(&_displayMode, 0, sizeof(_displayMode));
	//EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &_displayMode);

	EngineDescription _description;
	memset(&_description,0, sizeof(EngineDescription));
	_description.EngineFlag = //(Uint64)(ENGINE_SUPPORT_INPUT |
		(ENGINE_SUPPORT_DOUBLEBUFFER |
		EX_DIRECTX |
		ENGINE_SUPPORT_EXTENSION);
	_description.nVersion = EX_ENGINE_VERSION;
	_description.PixelType = (Uint)(ENGINE_RGB | ENGINE_ALPHA);

	//_description.FullScreen_Hz = _displayMode.dmDisplayFrequency;

	_description.BufferCount = 1;
	_description.AffinityCount = 1;

	_description.DepthBits = 24;
	_description.ColorBits = 32;
	_description.AccumBits = 8;
	_description.StencilBits = 8;

	return _description;
}
static EngineDescription ELTAPIENTRY EngineOpenGLDescription(void){
	//DEVMODE _displayMode;
	//memset(&_displayMode, 0, sizeof(_displayMode));
	//EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &_displayMode);

	EngineDescription defaultDescripton;
	memset(&defaultDescripton,0, sizeof(EngineDescription));
	defaultDescripton.nVersion = EX_ENGINE_VERSION;
	defaultDescripton.EngineFlag = (
		//ENGINE_WINDOW |
		//ENGINE_SUPPORT_INPUT |
		ENGINE_SUPPORT_DOUBLEBUFFER |
		EX_OPENGL);
	defaultDescripton.PixelType = (Uint)(ENGINE_RGB | ENGINE_ALPHA);


	//defaultDescripton.FullScreen_Hz = _displayMode.dmDisplayFrequency;

	defaultDescripton.BufferCount = 1;
	defaultDescripton.AffinityCount = 1;

	defaultDescripton.DepthBits = 24;
	defaultDescripton.ColorBits = 32;
	defaultDescripton.AccumBits = 0;
	defaultDescripton.StencilBits = 8;

	return defaultDescripton;
}

