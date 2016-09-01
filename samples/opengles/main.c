#include"./../../include/EngineExAPI.h"


#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif


int main(int argc, char** argv){
	ExChar title[256] = {0};
	ExWin win = NULL;
	ExWin drawable = NULL;
	ExEvent event = {0};
	ExSize size = {0};
	ExBoolean fullscreen = 0;

	if(!ExInit(ELT_INIT_EVERYTHING)){
		goto error;
	}

	ExGetPrimaryScreenSize(&size);
	win = ExCreateWindow(size.width / 4, size.height / 4, size.width / 2, size.height / 2, EX_OPENGLES);
	if(!win){
		ExError("Failed to create Window.\n");
		goto error;
	}
	ExShowWindow(win);

	ExSetWindowTitle(win, sprintf(title, "Create OpenGLES %d.%d%d Window." ,0,0,0));

	while(TRUE){
		while(ExPollEvent(&event)){
			if(event.event & EX_EVENT_KEY){
				if(event.key.ctrl && event.key.code == EXK_ENTER){
					fullscreen = ~fullscreen & 0x1;

				}

				if(event.key.code == EXK_ESCAPE){

				}

				if(event.key.code == EXK_q){
					goto error;
				}
			}

			if(event.event & EX_EVENT_SIZE){
				glViewport(0, 0, event.size.width, event.size.height);
			}
		}
	
		//ExSwapBuffers();
		continue;
	}	


	error:
	ExCloseWindow(win);
	ExQuit();
	return EXIT_SUCCESS;
}
