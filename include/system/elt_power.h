#ifndef _ELT_POWER_H_
#define _ELT_POWER_H_ 1
#include"../EngineEx.h"

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/*
 *	Get Power Info
 *	@return
 */
extern DECLSPEC Enum ELTAPIENTRY ExGetPowerInfo(Int32* sec, Int32* pct);



#ifdef  __cplusplus	/* C++ Environment */
}
#endif


#endif
