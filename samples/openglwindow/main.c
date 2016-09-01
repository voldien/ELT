#include"./../../include/EngineExAPI.h"
#include<GL/gl.h>


#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif


int main(int argc, char** argv){

	ExWin hwnd = NULL;
	ExEvent event = {0};
	ExSize size = {0};
	ExWin drawable = NULL;
	long time = 0;
	ExBoolean fullscreen = FALSE;


	/*
	 *	Initialize the library.
	 */
	if(!ExInit(ELT_INIT_EVERYTHING)){
		ExError("Failed to initialize ELT library.\n");
		goto error;
	}

	/*
	 *
	 */
	ExGetPrimaryScreenSize(&size);
	hwnd = ExCreateWindow(size.width / 4, size.height / 4, size.width / 2, size.height / 2, EX_OPENGL);
	if(!hwnd){
		ExError("Failed to create Window.\n");
		goto error;
	}

	ExShowWindow(hwnd);
	ExSetWindowTitle(hwnd, EX_TEXT("Sample : Create window!"));


	/*
	 *
	 */
	drawable = ExGetCurrentGLDrawable();
	time = ExGetHiResTime();
	while(TRUE){

		while(ExPollEvent(&event)){
			if(event.event & EX_EVENT_KEY){
				if(event.key.ctrl && event.key.code == EXK_ENTER){
					fullscreen = ~fullscreen & 0x1;
					ExGLFullScreen(fullscreen, hwnd, 0, 0);
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

		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(
				(2.0 * sin(0.000000001 * (double)time + 3.14)) / 2.0,
				(2.0 * cos(0.000000001 * (double)time - 1.60)) / 2.0,
				(2.0 * sin(0.000000001 * (double)time - 4.00)) / 2.0,
				1.0f
		);

		ExSwapBuffers(drawable);
		time = ExGetHiResTime();
		ExSleep(8);
		continue;
	}

	error:
	ExCloseWindow(hwnd);
	ExQuit();
	return EXIT_SUCCESS;
}
