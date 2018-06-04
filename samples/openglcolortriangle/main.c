#include"./../../include/EngineExAPI.h"
#include<GL/gl.h>

#include<GL/glew.h>
#include<GL/glx.h>
#include<GL/gl.h>

#ifdef EX_WINDOWS
	#pragma comment(lib,"OpenGL32.lib")
#elif defined(EX_LINUX)
	#include<X11/X.h>
#endif


extern char* vertex_shader;
extern char* fragment_shader;


char* vertex_shader = ""
"#version 330 core\n"
#ifdef GL_ES
"precision mediump float;\n"
#endif
"layout(location = 0) in vec3 vertex;\n"
"layout(location = 1) in vec4 color;\n"
"out vec4 vertexcolor;\n"
"void main(void){\n"
"	gl_Position = vec4(vertex,1.0);\n"
"	vertexcolor = color;\n"
"}\n";
 char* fragment_shader = ""
"#version 330 core"
"#ifdef GL_ES\n"
"#endif\n"
"layout(location = 0) out vec4 glColor;\n"
"in vec4 vertetxcolor;\n"
"void main(void){\n"
"	glColor = vertexcolor;\n"
"}\n";

struct vertex_color{
	float vertices[3];
	float color[4];
};



#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif

int main(int argc, char** argv){
	ExWin win = NULL;
	ExWin drawable = NULL;
	ExEvent event = {0};
	int program;
	int vshader;
	int fshader;
	int c_status;
	unsigned int vbo,vertex_location;

	float vertex_triangle[3][3] = {
		{1,0,0},
		{0,2,0},
		{-1,0,0}
	};
	struct vertex_color vertexcolor[] = {
		{{1.0f,0.0f,0.0f},{1.0f,0.0f,0.0f,1.0f}},
		{{0.0f,2.0f,0.0f},{0.0f,1.0f,0.0f,1.0f}},
		{{-1.0f,0.0f,0.0f},{0.0f,0.0f,1.0f,1.0f}}
	};



	/*
		Initialize ELT
	*/
	if(!ExInit(EX_INIT_EVERYTHING)){

	}
	
	/*
		Create Window 
		EX_OPENGL = opengl
		EX_OPENGL_ES = opengles
		EX_DIRECTX = directx (only window) and this example isn't compadiable 	
	*/
	win = ExCreateWindow(0, 0, 800, 600, EX_OPENGL);

	if(!win){	/* Failed to create window	*/
		ExErrorl(0,"Failed to Create Window\n");
	}

	if(!ExSetWindowTitle(win, argv[0]))	// Failed to set window title
		ExErrorl(0,"Failed to Set Title onto window %d\n",ExGetError());
	ExShowWindow(win);	
	
	glewInit();
	glViewport(0,0,800,600);
	/*
		Create shader program
	*/
	program = glCreateProgram();
	/*
		Create Vertex Shader
	*/
	vshader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vshader, 1, &vertex_shader, 0);
	glCompileShader(vshader);
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &c_status);
//	if(!c_status)ExError("Failed to Create Vertex Shader"); 

//	glAttachShader(program, vshader);
	/*
		Create Fragment Shader
	*/
	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, &fragment_shader,0);
	glCompileShader(fshader);
	glGetShaderiv(fshader, GL_COMPILE_STATUS, &c_status);
//	if(!c_status)ExError("Failed to Create Fragment shader");
	glAttachShader(program, vshader);
	glAttachShader(program, fshader);

	//glLinkProgram(program);
	///glUseProgram(program);
//	glBindAttribLocation(program, 0, "vertex");
//	glBindFragDataLocation(program, 0, "glColor");	
	glLinkProgram(program);
	
	glValidateProgram(program);
	/*
		Create VBO
	*/
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexcolor), vertexcolor, GL_STATIC_DRAW);


	glClearColor(0.4,0.4,0.4,1);
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);	
	glDisable(GL_BLEND);

	while(event.key.code != 13/* != ENTER*/){
		while(ExPollEvent(&event)){
			continue;
		}


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribPointer(0,4,GL_FLOAT, GL_FALSE,sizeof(float) * 4,(const void*)12);
		glDrawBuffer(GL_FRONT);
		glDrawArrays(GL_TRIANGLES,0, 3);
		//ExSleep(8);
		ExSwapBuffers(ExGetCurrentGLDC());
		continue;
	}


	ExShutDown();
	return EXIT_SUCCESS;
}
