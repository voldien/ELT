#include"elt_mutex.h"



ExMutex ExCreateMutex(void){
	ExMutex mutex;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);

	if(pthread_mutex_init(&mutex, NULL) < 0){

	}
	return mutex;
}

void ExDestroyMutex(ExMutex* mutex){
	if(pthread_mutex_destroy(mutex) < 0){

	}
}

void ExLockMutex(ExMutex mutex){
	pthread_mutex_lock(&mutex);
}

void ExUnLockMutex(ExMutex mutex){
	pthread_mutex_unlock(&mutex);
}



void ExTryLockMutex(ExMutex mutex){
	pthread_mutex_trylock(&mutex);
}
