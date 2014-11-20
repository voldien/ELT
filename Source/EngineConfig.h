/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef ENGINE_EX_C_H
#define ENGINE_EX_C_H
#include"EngineAssembly.h"
#ifdef EX_CPP
extern "C" {
#endif
typedef struct EngineDescriptionFileHader{
	Uint32 size;
	Uint32 offset;
	EngineDescription description;
}EngineDescFileHeader;

/* Read Config File  */
extern DECLSPEC ERESULT ELTAPIENTRY ExReadEngineConfig(const char* path, EngineDescription* engineDescription);
/* Write Config File */
extern DECLSPEC ERESULT ELTAPIENTRY ExWriteEngineConfig(const char* path, EngineDescription* description);
/* Set Data */
extern DECLSPEC Boolean ELTAPIENTRY ExSetDataEngineConfig(char* ParameterType, char* ParameterInfo, EngineDescription* engineDescription);
/* Get Data */

/**/
extern DECLSPEC Boolean ELTAPIENTRY ExLoadEngineDesc(const char* path, EngineDescription* engineDescription);
/**/
extern DECLSPEC void ELTAPIENTRY ExSaveEngineDesc(const char* path, EngineDescription* engineDescription);


#ifdef EX_CPP
}
#endif
#endif
