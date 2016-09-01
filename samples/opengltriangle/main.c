#include"./../../include/EngineExAPI.h"
#include"./../../include/graphic.h"
//#include<GL/glew.h>
#include<GL/glx.h>
#include<GL/gl.h>
#ifdef EX_WINDOWS
#	pragma comment(lib,"OpenGL32.lib")
#elif defined(EX_LINUX)
#	include<X11/X.h>	
#endif


char* vertex_shader = ""
"#version 330 core\n"
"#ifdef GL_ES\n"
"precision mediump float;\n"
"#endif\n"
"layout(location = 0) in vec3 vertex;\n"
"out vec3 pos;\n"
"void main(void){\n"
"	gl_Position = vec4(vertex.x, vertex.y, vertex.z, 1.0);\n"
"	pos = vertex;\n"
"}\n";

 char* fragment_shader = ""
"#version 330 core\n"
"#ifdef GL_ES\n"
"precision mediump float;\n"
"#endif\n"
"layout(location = 0) out vec4 fragColor;\n"
"in vec3 pos;\n"
"void main(void){\n"
"	fragColor = vec4(1.0,1.0,0.0,1.0);\n"
"}\n";


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
	int vao = 0;
	unsigned int vbo;
	unsigned int vertex_location;
	float pos[3];
	ExBoolean fullscreen;
	ExShader shader;
	int status;

	float vertex_triangle[3][3] = {
		{-1.0f, -1.0f, 0.0f},
		{0.0f,   1.0f, 0.0f},
		{1.0f,  -1.0f, 0.0f},
	};


	/*
		Initialize ELT
	*/
	if(!ExInit(ELT_INIT_EVERYTHING)){
		return EXIT_FAILURE;
	}


	/*
		Create Window 
		EX_OPENGL = opengl
		EX_OPENGL_ES = opengles
		EX_DIRECTX = directx (only window) and this example isn't compadiable 	
	*/
	ExGetPrimaryScreenSize(&size);
	ExOpenGLSetAttribute(EX_OPENGL_MAJOR_VERSION, 3);
	ExOpenGLSetAttribute(EX_OPENGL_MINOR_VERSION, 3);
	ExOpenGLSetAttribute(EX_OPENGL_CONTEXT_PROFILE_MASK, EX_GL_CONTEXT_PROFILE_CORE);
	ExOpenGLSetAttribute(EX_OPENGL_CONTEXT_FLAGS, 0);

	win = ExCreateWindow(size.width / 4, size.height / 4, size.width / 2, size.height / 2, EX_OPENGL);
	if(!win){	// Failed to create window
		ExErrorl(0, "Failed to Create Window %d\n", ExGetError());
	}

	ExSetWindowTitle(win, argv[0]);
	ExShowWindow(win);

	status = ExLoadShaderv(&shader, vertex_shader, fragment_shader, NULL, NULL, NULL);
	if(status == 0)
		return EXIT_FAILURE;

	/*
		Create VBO
	*/
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 12, (void*)NULL);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_triangle), vertex_triangle, GL_STATIC_DRAW);

	glBindVertexArray(0);

	glClearColor(0.4,0.4,0.4,1.0);
	ExGetWindowSizev(win,&size);
	glViewport(0, 0, size.width, size.height);

	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	drawable = ExGetCurrentGLDrawable();
	glUseProgram(shader.program);
	glDisable(GL_CULL_FACE);
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

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES,0, sizeof(vertex_triangle) /sizeof(vertex_triangle[0]));
		glBindVertexArray(0);


		ExSwapBuffers(drawable);
	}

	error:
	ExCloseWindow(win);
	ExQuit();
	return EXIT_SUCCESS;
}
