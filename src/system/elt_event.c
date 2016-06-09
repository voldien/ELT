#include"system/elt_event.h"
#include"elt_assert.h"
#include"elt_def.h"

#ifdef EX_WINDOWS
#	include"system/win/win_wndproc.h"
#	define WIN32_LEAN_AND_MEAN
#	include<windows.h>
#	include <winuser.h>
#	include<windowsx.h>
#	include<ws2dnet.h>
#elif defined(EX_ANDROID)
#   include<errno.h>
#   include<android/window.h>
#   include<android/rect.h>
#   include<android/input.h>
#   include<android/looper.h>
#   include<android/sensor.h>
#elif defined(EX_MAC)

#endif
