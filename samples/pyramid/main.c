#include"./../../include/EngineExAPI.h"
#include"../common/common.h"
#include<GL/gl.h>


#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif


int main(int argc, char** argv){

	ExWin win = NULL;
	ExEvent event = {0};
	ExSize size = {0};
	ExWin drawable = NULL;
	long time = 0;
	ExBoolean fullscreen = FALSE;
	unsigned int vao;
	unsigned int vao;

	/*
	v  0  0  0
	v  1  0  0
	v  1  1  0
	v  0  1  0
	v  0.5  0.5  1.6

	f  5  2  3
	f  4  5  3
	f  6  3  2
	f  5  6  2
	f  4  6  5
	f  6  4  3
	*/

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
	win = ExCreateWindow(size.width / 4, size.height / 4, size.width / 2, size.height / 2, EX_OPENGL);
	if(!win){
		ExError("Failed to create Window.\n");
		goto error;
	}

	ExShowWindow(win);
	ExSetWindowTitle(win, EX_TEXT("Sample : Create window!"));







	error:
	ExCloseWindow(win);
	ExQuit();
	return EXIT_SUCCESS;

}
