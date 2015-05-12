#include"graphic/shader.h"
#include"system/eltfile.h"
#include<GL/gl.h>


int getShaderProgramSize(unsigned int program){
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
		shad->ver = compileShaderSource(cvertexfilename,&v_source,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
		//InitShader(shad, v_source, GL_VERTEX_SHADER);
	}
	if(cfragmentfilename){
		shad->fra = compileShaderSource(cfragmentfilename,&f_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
	if(cgeometryfilename){
		shad->geo = compileShaderSource(cgeometryfilename,&g_source,GL_GEOMETRY_SHADER);
	}
	if(ctesscfilename){
		shad->tesc = compileShaderSource(ctesscfilename,&tc_source,GL_TESS_CONTROL_SHADER);
	}
	if(ctessefilename){
		shad->tese = compileShaderSource(ctessefilename,&te_source,GL_TESS_EVALUATION_SHADER);
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
		shad->ver = compileShaderSourcev(&cvertex_source,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
	}
	if(cfragment_source){
		shad->fra = compileShaderSourcev(&cfragment_source,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
	if(cgeometry_source){
		shad->geo = compileShaderSourcev(&cgeometry_source,GL_GEOMETRY_SHADER);
		glAttachShader(shad->program,shad->geo);
	}
	if(ctess_c_source){
		shad->tesc = compileShaderSourcev(&ctess_c_source,GL_TESS_CONTROL_SHADER);
		glAttachShader(shad->program,shad->tesc);
	}
	if(ctess_e_source){
		shad->tese = compileShaderSourcev(&ctess_e_source,GL_TESS_EVALUATION_SHADER);
		glAttachShader(shad->program,shad->tese);
	}

	glLinkProgram(shad->program);
	ShaderCompileLog(shad->program,GL_PROGRAM);
	return 1;
}


int compileShaderSource(const char* strPath,char** source, unsigned int flag){
	char* data;
	int shader, c_message;
	if(!strlen(strPath))return -1;

	if(ExLoadFile(strPath,(void**)&data) != -1){

		shader = glCreateShader(flag);
		glShaderSource(shader, 1,(const char**)&data,0);
		glCompileShader(shader);
		// validate
		glGetShaderiv(shader, GL_COMPILE_STATUS, &c_message);
		if(!c_message)
			ExError("Error to compile %s", strPath);

		if(!source)
			free(data);
		else
			*source = data;
	}else{ExError("Invalid Path %s",strPath); return -1;}
	return shader;
}
int compileShaderSourcev(const char** source, unsigned int flag){
	int shader;
	if(!source)
		return -1;
	if(!strlen(source[0]))return -1;

	shader = glCreateShader(flag);
	glShaderSource(shader,1,source, 0);
	glCompileShader(shader);
	ShaderCompileLog(shader,flag);
	return shader;
}


extern int ShaderCompileLog(unsigned int program,unsigned int shaderflag){
	int status,validate;
	char message[256];
	switch(shaderflag){
	case GL_VERTEX_SHADER:
	case GL_FRAGMENT_SHADER:
	case GL_GEOMETRY_SHADER:
	case GL_TESS_CONTROL_SHADER:
	case GL_TESS_EVALUATION_SHADER:
		glGetShaderiv(program, GL_COMPILE_STATUS, &status);
		break;
	case GL_LINK_STATUS:
	case GL_PROGRAM:
	glGetProgramiv(program, GL_LINK_STATUS,&status);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &validate);
		break;
	default:return 0;
	}
	if(!status && program != GL_PROGRAM)
		glGetShaderInfoLog(program,sizeof(message),NULL, message);
	else if(!status)
		glGetProgramInfoLog(program,sizeof(message),NULL, message);
	if(!status){
		printf("Error message when compiling glsl Shader\n%s", message);
		return 0;
	}
	return 1;
}



int getShaderSource(unsigned int program, unsigned int shader_flag, char** source){
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
