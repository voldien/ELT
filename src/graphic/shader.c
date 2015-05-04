#include"graphic/shader.h"
#include<GL/gl.h>


unsigned int getShaderProgramSize(unsigned int program){
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

int loadShader(struct shader_header* shad,const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename){
	char* v_source,*f_source,*g_source,*tc_source,*te_source;
	v_source = f_source = g_source = tc_source = te_source = NULL;

	shad->program = glCreateProgram();
	if(cvertexfilename){
		shad->ver = CompileShaderSource(cvertexfilename,&v_source,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
		//InitShader(shad, v_source, GL_VERTEX_SHADER);
	}
	if(cfragmentfilename){
		shad->fra = CompileShaderSource(cfragmentfilename,&f_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
	if(cgeometryfilename){
		shad->geo = CompileShaderSource(cgeometryfilename,&g_source,GL_GEOMETRY_SHADER);
	}
	if(ctesscfilename){
		shad->tesc = CompileShaderSource(ctesscfilename,&tc_source,GL_TESS_CONTROL_SHADER);
	}
	if(ctessefilename){
		shad->tese = CompileShaderSource(ctessefilename,&te_source,GL_TESS_EVALUATION_SHADER);
	}

	glLinkProgram(shad->program);
	ShaderCompileLog(shad->program,GL_PROGRAM);

	free(v_source);
	free(f_source);
	free(g_source);
	free(tc_source);
	free(te_source);
	return 1;
}
int loadShaderv(struct shader_header* shad, const char* cvertex_source,const char* cfragment_source,const char* cgeometry_source,const char* ctess_c_source, const char* ctess_e_source){
	if(!shad)
		return 0;
	shad->program = glCreateProgram();
	if(cvertex_source){
		shad->ver = CompileShaderSourcev(&cvertex_source,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
	}
	if(cfragment_source){
		shad->fra = CompileShaderSourcev(&cfragment_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
	if(cgeometry_source){
		shad->geo = CompileShaderSourcev(&cgeometry_source,GL_GEOMETRY_SHADER);
		glAttachShader(shad->program,shad->geo);
	}
	if(ctess_c_source){
		shad->tesc = CompileShaderSourcev(&ctess_c_source,GL_TESS_CONTROL_SHADER);
		glAttachShader(shad->program,shad->tesc);
	}
	if(ctess_e_source){
		shad->tese = CompileShaderSourcev(&ctess_e_source,GL_TESS_EVALUATION_SHADER);
		glAttachShader(shad->program,shad->tese);
	}

	glLinkProgram(shad->program);
	ShaderCompileLog(shad->program,GL_PROGRAM);
	return 1;
}


int GetShaderSource(unsigned int program, unsigned int shader_flag, char** source){
	int len;
	glGetShaderiv(program, GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;
	source[0] = (char*)malloc(len);
	glGetShaderSource(program, len, NULL, source[0]);
	//glGetProgramiv(program,
	return 1;
}
char* GetShaderSourcefast(unsigned int program, unsigned int shader_flag){
	int len;
	char* source;
	glGetShaderiv(program, GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;
	source = (char*)malloc(len);
	glGetShaderSource(program, len, NULL, source);
	return source;
}
