#include"./../../include/EngineExAPI.h"
#include<GL/gl.h>
#include<CL/cl.h>
#include<CL/cl_gl.h>

#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif



int main(int argc, char** argv){
	ExWin win = NULL;
	ExWin drawable = NULL;
	ExEvent event = {0};
	ExSize size = {0};
	ExOpenCLContext clc;
	ExBoolean fullscreen = 0;
	cl_program program;
	cl_kernel ker;
	cl_command_queue queue;
	cl_mem mem;
	cl_device_id id;


	if(!ExInit(ELT_INIT_EVERYTHING)){

	}



	win = ExCreateWindow(size.width / 4, size.height / 4, size.width / 2, size.height / 2, EX_OPENGL);
	if(!win){	// Failed to create window
		ExErrorl(0, "Failed to Create Window %d\n", ExGetError());
	}
	ExSetWindowTitle(win, argv[0]);
	ExShowWindow(win);

	clc = ExCreateCLSharedContext(ExGetCurrenOpenGLContext(), win, 0);
	if(!clc){
		goto error;
	}

	if(!ExQueryCLContext(clc, &id, CL_DEVICE_TYPE_GPU)){

	}

	queue = ExCreateCommandQueue(clc, id);
	if(!queue){

	}

	program = ExCreateProgram(clc, id, "gameoflife.cl", NULL);
	if(!program){

	}

	ker = clCreateKernel(program, "life", NULL);
	if(!ker){

	}



	drawable = ExGetCurrentGLDrawable();
	while(event.key.code != EXK_q/* != ENTER*/){
		while(ExPollEvent(&event)){
			if(event.event & EX_EVENT_KEY){
				if(event.key.ctrl && event.key.code == EXK_ENTER){
					fullscreen = ~fullscreen & 0x1;
					ExGLFullScreen(fullscreen, win, 0, 0);
				}

				if(event.key.code == EXK_ESCAPE){

				}
			}

			if(event.event & EX_EVENT_SIZE){
				//glViewport(0, 0, event.size.width, event.size.height);
			}

			if(event.event & EX_EVENT_QUIT){
				goto error;
			}
		}


		ExSwapBuffers(drawable);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}




	error:

	ExDestroyCLContext(clc);
	ExCloseWindow(win);
	ExQuit();
	return EXIT_SUCCESS;
}
