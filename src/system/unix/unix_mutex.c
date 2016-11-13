#include"elt_mutex.h"
#include"system/elt_errorhandler.h"

#include<pthread.h>


ExMutex ExCreateMutex(void){
	pthread_mutex_t* mutex;
	pthread_mutexattr_t attr;
	if(pthread_mutexattr_init(&attr)  < 0){

	}

	mutex = calloc(1, sizeof(*mutex));
	if(mutex){
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		//pthread_mutexattr_set

		if(pthread_mutex_init(mutex, &attr) < 0){
			ExSetError(E_ERROR_SYSTEM);
			free(mutex);
			mutex = NULL;
		}
	}
	pthread_mutexattr_destroy(&attr);
	return mutex;
}


void ExDestroyMutex(ExMutex* mutex){
	if(pthread_mutex_destroy(mutex) < 0){

	}
	free(mutex);
}

void ExLockMutex(ExMutex mutex){
	if(pthread_mutex_lock((pthread_mutex_t*)mutex) < 0){

	}
}

void ExUnLockMutex(ExMutex mutex){
	if(pthread_mutex_unlock((pthread_mutex_t*)mutex) < 0){

	}
}

void ExTryLockMutex(ExMutex mutex){
	if(pthread_mutex_trylock((pthread_mutex_t*)mutex)){

	}
}
