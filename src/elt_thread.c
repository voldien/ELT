#include"elt_thread.h"
#include"elt_def.h"
#ifdef EX_WINDOWS           /*  Windows */
#include<windef.h>
#include<windows.h>
#   define EX_START_THREAD(x)	ResumeThread( ( x ) )
#elif defined(EX_UNIX)   /*  Linux & android  */
#   define _GNU_SOURCE
#   define __USE_GNU
#   include<pthread.h>
#   include<errno.h>
#   include<unistd.h>
#   include <sched.h>
#   include <stdlib.h>
#   include <unistd.h>
#   include <stdio.h>
#   include <assert.h>
#   define EX_START_THREAD(x)	pthread_detach( ( x ))  /*TODO change*/
#endif
#include<signal.h>


//http://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

