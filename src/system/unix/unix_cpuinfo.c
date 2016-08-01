#include"elt_cpuinfo.h"
#   include<unistd.h>
#include<setjmp.h>

Int32 ExGetCPUCount(void){
	return sysconf(_SC_NPROCESSORS_ONLN);
//#elif defined(__IRIX__)
//	   num_cpus = sysconf(_SC_NPROC_ONLN);
//#elif defined(_SC_NPROCESSORS_ONLN)
//	   /* number of processors online (SVR4.0MP compliant machines) */
//          num_cpus = sysconf(_SC_NPROCESSORS_ONLN);
//#elif defined(_SC_NPROCESSORS_CONF)
	   /* number of processors configured (SVR4.0MP compliant machines) */
//          num_cpus = sysconf(_SC_NPROCESSORS_CONF);
//#endif
}
