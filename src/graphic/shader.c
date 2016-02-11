#include"graphic/shader.h"
#include"system/elt_file.h"


#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#undef GL_ES_VERSION_2_0
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
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
	int numShader;
	unsigned int shad[16];
	fsize = 0;

	glGetAttachedShaders(program,sizeof(shad) / sizeof(shad[0]),&numShader,shad);


	for(i = 0; i < numShader; i++){
		glGetShaderiv(shad[i], GL_SHADER_SOURCE_LENGTH,&size);
		fsize+=size;
	}
	return fsize;
}


int ExSetProgramShader(int program, int shader){
	int count;
	int x;
	int newtype;
	int shaders[5];
	glGetAttachedShaders(program,4,&count,shaders);
	glGetShaderiv(shader,GL_SHADER_TYPE,&newtype);
	for(x = 0; x < count; x++){
		int type;
		glGetShaderiv(shaders[x], GL_SHADER_TYPE,&type);
		if(type == newtype)
			break;
	}
	glDetachShader(program,shaders[x]);

	glAttachShader(program,shader);
	glLinkProgram(program);

#if !(defined(GL_ES_VERSION_1_0) || defined(GL_ES_VERSION_2_0))
	return ExShaderCompileLog(program,GL_PROGRAM);
#else
	return ExShaderCompileLog(program,0);
#endif

}


int ExLoadShader(ExShader* shad,const char* cvertexfilename, const char* cfragmentfilename, const char* cgeometryfilename, const char* ctesscfilename, const char* ctessefilename){
	char* v_source;
	char* f_source;
	char* g_source;
	char* tc_source;
	char* te_source;
	int error;
	v_source = f_source = g_source = tc_source = te_source = NULL;

	shad->program = glCreateProgram();


	if(cvertexfilename){
		shad->ver = ExCompileShaderSource(cvertexfilename,NULL,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
	}
	if(cfragmentfilename){
		shad->fra = ExCompileShaderSource(cfragmentfilename,NULL,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
#if !defined(GL_ES_VERSION_2_0)
	if(cgeometryfilename){
		shad->geo = ExCompileShaderSource(cgeometryfilename,&g_source,GL_GEOMETRY_SHADER);
	}
	if(ctesscfilename){
		shad->tesc = ExCompileShaderSource(ctesscfilename,&tc_source,GL_TESS_CONTROL_SHADER);
	}
	if(ctessefilename){
		shad->tese = ExCompileShaderSource(ctessefilename,&te_source,GL_TESS_EVALUATION_SHADER);
	}
#endif
	/**/
	free(v_source);
	free(f_source);
	free(g_source);
	free(tc_source);
	free(te_source);


	glLinkProgram(shad->program);

#if !defined(GL_ES_VERSION_2_0)
	error = ExShaderCompileLog(shad->program,GL_PROGRAM);
	if(!error){

	}
	return error;
#endif

	return 1;
}

int ExLoadShaderv(ExShader* shad, const char* cvertexSource,const char* cfragmentSource,const char* cgeometrySource,const char* ctessCSource, const char* ctessESource){
	int error;
	if(!shad)
		return 0;
	shad->program = glCreateProgram();

	if(cvertexSource){
		shad->ver = ExCompileShaderSourcev(&cvertexSource,GL_VERTEX_SHADER);
		glAttachShader(shad->program,shad->ver);
	}
	if(cfragmentSource){
		shad->fra = ExCompileShaderSourcev(&cfragmentSource,GL_FRAGMENT_SHADER);
		glAttachShader(shad->program,shad->fra);
	}
#if !defined(GL_ES_VERSION_2_0)
	if(cgeometrySource){
		shad->geo = ExCompileShaderSourcev(&cgeometrySource,GL_GEOMETRY_SHADER);
		glAttachShader(shad->program,shad->geo);
	}
	if(ctessCSource){
		shad->tesc = ExCompileShaderSourcev(&ctessCSource,GL_TESS_CONTROL_SHADER);
		glAttachShader(shad->program,shad->tesc);
	}
	if(ctessESource){
		shad->tese = ExCompileShaderSourcev(&ctessESource,GL_TESS_EVALUATION_SHADER);
		glAttachShader(shad->program,shad->tese);
	}
#endif

	glValidateProgram(shad->program);
	glLinkProgram(shad->program);

#if !defined(GL_ES_VERSION_2_0)
	error = ExShaderCompileLog(shad->program,GL_PROGRAM);
	if(!error){
		ExDeleteShaderProgram(shad);
	}
	return error;
#endif
	return 1;
}

int ExDeleteShaderProgram(ExShader* header){
	int error;
	glDeleteProgram(header->program);
	glDeleteShader(header->ver);
	glDeleteShader(header->fra);
	glDeleteShader(header->geo);
	glDeleteShader(header->tesc);
	glDeleteShader(header->tese);

	error = glIsProgram(header->program);

	memset(header,0,sizeof(*header));


	return error ? 0 : error;
}

int ExCompileShaderSource(const char* strPath,char** source, unsigned int flag){
	char* data;
	int shader;
	int c_message;
	if(!strlen(strPath))
		return -1;

	if(ExLoadFile(strPath,(void**)&data) != -1){

		/**/
		if((shader = ExCompileShaderSourcev(&data,flag)) < 0)
			printf("failed to compile %s\n",strPath);

		/**/
		if(!source)
			free(data);
		else
			*source = data;

	}else{
		printf("Invalid Path %s",strPath);
		return -1;
	}
	return shader;
}

int ExCompileShaderSourcev(const char** source, unsigned int flag){
	int shader;
	int status;
	int error;
	if(!source || !source[0])
		return -1;
	if(!strlen(source[0]))
		return -1;

	shader = glCreateShader(flag);
	glShaderSource(shader, 1, source, NULL);
	glCompileShader(shader);
	error = ExShaderCompileLog(shader, flag);

	return shader;
}

int ExShaderCompileLog(unsigned int program,unsigned int shaderflag){
	int status,validate;
	char log[512];

	/* check if shader*/
	if(glIsProgram(program)){
		glGetProgramiv(program, GL_LINK_STATUS,&status);
		glGetProgramiv(program, GL_VALIDATE_STATUS,&validate);
		if(status & validate)
			return TRUE;

		if(!status){
			glGetProgramInfoLog(program, sizeof(log),NULL,log);
			printf("\x1B[31m""Failed to compile shader\n%s", log);
		}
		return FALSE;
	}

	glGetShaderiv(program,GL_COMPILE_STATUS,&status );

	if(!status){

		switch(shaderflag){
		case GL_VERTEX_SHADER:
			glGetShaderInfoLog(program, sizeof(log),NULL,log);
			printf("\x1B[31m""Failed to Compile Vertex Shader |\n %s \n",log);
			break;
		case GL_FRAGMENT_SHADER:
			glGetShaderInfoLog(program, sizeof(log),NULL,log);
			printf("\x1B[31m""Failed to Compile Fragment Shader]\n%s \n", log);
			break;
	#if !defined(GL_ES_VERSION_2_0)
		case GL_GEOMETRY_SHADER:
			glGetShaderInfoLog(program, sizeof(log),NULL,log);
			printf("\x1B[31m""Failed to Compile GEOMETRY Shader]\n%s \n", log);
			break;
		case GL_TESS_CONTROL_SHADER:

			glGetShaderInfoLog(program, sizeof(log),NULL,log);
			printf("\x1B[31m ""Failed to Compile tessellation control  Shader]\n%s \n", log);
			break;
		case GL_TESS_EVALUATION_SHADER:
			glGetShaderInfoLog(program, sizeof(log),NULL,log);
			printf("\x1B[31m Failed to Compile tessellation evolutation Shader]\n%s \n", log);
			break;
	#endif
			break;
			default:return TRUE;
		}
	}

	return status;
}

int ExShaderCompileLogv(unsigned int program,unsigned int shaderflag, char* log){

	return TRUE;
}



int ExGetShaderSource(unsigned int shader, char** source){
	int len;
	if(!glIsShader(shader))
		return 0;

	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;

	source[0] = (char*)malloc(len);
	glGetShaderSource(shader, len, &len, source[0]);
	//glGetProgramiv(program,
	return 1;
}

char* getShaderSourcefast(unsigned int shader){
	int len;
	char* source;
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH,&len);
	if(!len)
		return 0;

	source = (char*)malloc(len);
	glGetShaderSource(shader, len, NULL, source);
	return source;
}
