#include<ELT/elt.h>
#include<GL/gl.h>


#if defined(EX_WINDOWS)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif


int main(int argc, char** argv){

	ExEvent event = {0};
	ExWin window;
	ExShader shadowshader;
	ExShader diffuseshader;

	assert(ExInit(EX_INIT_NONE));
	window = createOpenglWindow();

	ExLoadShader(&shadowshader, "../common/shadowV.glsl", "../common/shadowF.glsl", NULL, NULL, NULL);
	ExLoadShader(&diffuseshader, "../common/shadowV.glsl", "../common/shadowF.glsl", NULL, NULL, NULL);


	glClearColor(1,0,0,1);
	while(1){

		while(ExPollEvent(&event)){

		}


		ExSwapBuffers(ExGetCurrentGLDrawable());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}
