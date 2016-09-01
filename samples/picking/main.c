#include"./../../include/EngineExAPI.h"
#include<GL/gl.h>


#if defined(EX_WINDOWS) && !defined(_CONSOLE)
INT CALLBACK WinMain(HINSTANCE h, HINSTANCE p, LPSTR argv, INT argc){
	return main(argc,argv);
}
#endif
int main(int argc, char** argv){}
