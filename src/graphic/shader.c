#include"graphic/shader.h"
#include"system/eltfile.h"

#ifdef GL_ES_VERSION_2_0
	#include<GLES/gl2.h>
	#include<GLES/gl2ext.h>
	#include<GLES/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else
	#include<GL/gl.h>
	#include<GL/glu.h>
	#include<GL/glext.h>
#endif


int ExGetShaderProgramSize(unsigned int program){
	unsigned int i,fsize;
	int size;
	int shad_num;
	unsigned int mshad[10];
	fsize = 0;

	glGetAttachedShaders(program,5,&shad_num,mshad);

	for(i=0;i<shad_num;i++){
		glGetShaderiv(mshad[i], GL_SHADER_SOURCE_LENGTH,&size);
		fsize+=size;
	}
	return fsize;
}

int ExLoadShader(struct shader_header* shad,const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename){
	char* v_source,*f_source,*g_source,*tc_source,*te_source;
	v_source = f_source = g_source = tc_source = te_source = NULL;

	shad->program = glCreateProgram();
	if(cvertexfilename){
		shad->ver = ExCompileShaderSource(cvertexfilename,&v_source,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);

	}
	if(cfragmentfilename){
		shad->fra = ExCompileShaderSource(cfragmentfilename,&f_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
	if(cgeometryfilename){
		shad->geo = ExCompileShaderSource(cgeometryfilename,&g_source,GL_GEOMETRY_SHADER);
	}
	if(ctesscfilename){
		shad->tesc = ExCompileShaderSource(ctesscfilename,&tc_source,GL_TESS_CONTROL_SHADER);
	}
	if(ctessefilename){
		shad->tese = ExCompileShaderSource(ctessefilename,&te_source,GL_TESS_EVALUATION_SHADER);
	}

	/**/
	free(v_source);
	free(f_source);
	free(g_source);
	free(tc_source);
	free(te_source);


	glLinkProgram(shad->program);
	return ExShaderCompileLog(shad->program,GL_PROGRAM);;
}
int ExLoadShaderv(struct shader_header* shad, const char* cvertex_source,const char* cfragment_source,const char* cgeometry_source,const char* ctess_c_source, const char* ctess_e_source){
	if(!shad)
		return 0;
	shad->program = glCreateProgram();
	if(cvertex_source){
		shad->ver = ExCompileShaderSourcev(&cvertex_source,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
	}
	if(cfragment_source){
		shad->fra = ExCompileShaderSourcev(&cfragment_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
	if(cgeometry_source){
		shad->geo = ExCompileShaderSourcev(&cgeometry_source,GL_GEOMETRY_SHADER);
		glAttachShader(shad->program,shad->geo);
	}
	if(ctess_c_source){
		shad->tesc = ExCompileShaderSourcev(&ctess_c_source,GL_TESS_CONTROL_SHADER);
		glAttachShader(shad->program,shad->tesc);
	}
	if(ctess_e_source){
		shad->tese = ExCompileShaderSourcev(&ctess_e_source,GL_TESS_EVALUATION_SHADER);
		glAttachShader(shad->program,shad->tese);
	}

	glLinkProgram(shad->program);
	return ExShaderCompileLog(shad->program,GL_PROGRAM);

}


int ExCompileShaderSource(const char* strPath,char** source, unsigned int flag){
	char* data;
	int shader, c_message;
	if(!strlen(strPath))return -1;

	if(ExLoadFile(strPath,(void**)&data) != -1){

		/**/
		if((shader = ExCompileShaderSourcev(&data,flag)) < 0)
			printf("failed to compile %s\n",strPath);

		/**/
		if(!source)
			free(data);
		else
			*source = data;
	}else{printf("Invalid Path %s",strPath); return -1;}
	return shader;
}
int ExCompileShaderSourcev(const char** source, unsigned int flag){
	int shader;
	int status;
	if(!source)
		return -1;
	if(!strlen(source[0]))return -1;

	shader = glCreateShader(flag);
	glShaderSource(shader,1,source, 0);
	glCompileShader(shader);
	ExShaderCompileLog(shader,flag);

	/*	validate shader	*/
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
	if(!status){
		glDeleteShader(shader);
		return -1 ;
	}
	return shader;
}


extern int ExShaderCompileLog(unsigned int program,unsigned int shaderflag){
	int status,validate;
	char log[256];
	switch(shaderflag){
	case GL_VERTEX_SHADER:
		glGetShaderInfoLog(program, sizeof(log),NULL,log);
		printf("[Failed to Compile Vertex Shader]\n %s \n",log);
		break;
	case GL_FRAGMENT_SHADER:
		glGetShaderInfoLog(program, sizeof(log),NULL,log);
		printf("[Failed to Compile Fragment Shader]\n%s \n", log);
		break;
	case GL_GEOMETRY_SHADER:
		glGetShaderInfoLog(program, sizeof(log),NULL,log);
		printf("[Failed to Compile GEOMETRY Shader]\n%s \n", log);
		break;
	case GL_TESS_CONTROL_SHADER:

		glGetShaderInfoLog(program, sizeof(log),NULL,log);
		printf("[Failed to Compile tessellation control  Shader]\n%s \n", log);
		break;
	case GL_TESS_EVALUATION_SHADER:
		glGetShaderInfoLog(program, sizeof(log),NULL,log);
		printf("[Failed to Compile tessellation evolutation Shader]\n%s \n", log);
		break;
	case GL_LINK_STATUS:
	case GL_PROGRAM:
		glGetProgramiv(program, GL_LINK_STATUS,&status);
		glGetProgramiv(program, GL_VALIDATE_STATUS, &validate);
		printf("Error message when compiling glsl Shader\n%s", log);
		return status;
		break;
		default:return 0;
	}
	return 1;
}



int ExGetShaderSource(unsigned int program, unsigned int shader_flag, char** source){
	int len;
	glGetShaderiv(program, GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;
	source[0] = (char*)malloc(len);
	glGetShaderSource(program, len, NULL, source[0]);
	//glGetProgramiv(program,
	return 1;
}
char* getShaderSourcefast(unsigned int program, unsigned int shader_flag){
	int len;
	char* source;
	glGetShaderiv(program, GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;
	source = (char*)malloc(len);
	glGetShaderSource(program, len, NULL, source);
	return source;
}
