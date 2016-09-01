#include"./../../include/EngineExAPI.h"


#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif


int main(int argc, char** argv){
	ExWin win;
	ExEvent event = {0};


	if(!ExInit(ELT_INIT_EVERYTHING)){
		ExErrorl(0,"Failed to Create Window %d\n", ExGetError());
	}

	win = ExCreateWindow(0,0,512,512,0);
	if(!win)
		ExErrorl(0,"Failed to Create Window %d\n", ExGetError());


	ExShowWindow(win);
	ExSetWindowTitle(win, argv[0]);
	//	ExErrorl(0,"Failed to Set Title onto window %d\n",ExGetError());


	while(event.key.code != 13){
		while(ExPollEvent(&event)){


			continue;
		}


		ExSleep(8);
		continue;
	}
	return EXIT_SUCCESS;
}
