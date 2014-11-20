/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef SHADER_FILE_H
#define SHADER_FILE_H
#pragma warning(disable : 4996)
#ifndef CMD_LIB_H
	#include<Cmd/cmdlib.h>
#endif

#ifdef __cplusplus // C++ environment
extern "C"{
#endif
#define SHADER_COLLECTION_FILE_EXT ".sc"
#define SHADER_COLLECTION_FILE_DESC "shader collection"
#define SHADER_COLLECTION_SIGNATURE ".sc"

#define SHADER_FILE__FILE_EXT ".sf"
#define SHADER_FILE__FILE_DESC "shader file"

struct shader_name_list{
	unsigned int num;
	char* list;
};
typedef struct shader_function{
	unsigned int csize;
	unsigned int coffset;
}ShaderFuncHeader;
typedef struct shader_file{
	unsigned int csize;
	unsigned int num_source;
	unsigned int flag;
}ShaderFileHeader;
typedef struct shader_Collection_File{
	unsigned char signature[4];
	unsigned int csize;
	unsigned int cversion;
	unsigned int flag;
	unsigned int coffset;
	unsigned int fileoffset;
	unsigned int funcoffset;
	unsigned int num_file;
	unsigned int num_function;
}ShaderBundleHeader,ShaderCollectionFile;

/*
	// check if file exists
	// remark:
*/
//#define ExistShaderCollection(cfilename) FileExist(cfilename)
extern Boolean ExistShaderCollection(const char*cfilename);
/*
	// create shader collection file
	// create a empty shader collection file
*/
extern Boolean CreateShaderCollection(const char* cfilename);
/*
	// create shader file
	// Remark:
*/
extern Boolean CreateShaderFile(ShaderFileHeader** shaderfile,const char* _Str_shader_name, const char* _Str_vertex_source, const char* _Str_fragment_source, const char* _Str_geometry_source,const char* _Str_tesselation_control_source,const char* _Str_tesselation_evolution_source);
/*
	// path to file on hard drive
*/
extern Boolean CreateShaderFile2(ShaderFileHeader** shaderfile, const char* c_Str_shader_name, const char* cvertexfilename,const char* cfragmentfilename,const char* cgeometryfilename,const char* ctesselation_c_filename,const char* ctesselation_e_filename);

/*
	// save shader file to hardriver
*/
extern Boolean SaveShaderFile(const char* cfilename,const  ShaderFileHeader* shaderfile);
extern Boolean LoadShaderFile(const char* cfilename, ShaderFileHeader** shaderfile);

/*
	// append shaderfile into shaderCollection
*/
extern void AppendShaderFile(const char* cfilename, ShaderFileHeader* shaderfile); 
extern void InsertShaderFile(const char* cfilename, const char* cname, ShaderFileHeader* shaderfile);
/*
	// append shader function into shaderCollection
*/
extern void AppendShaderFunction(const char* cfilename, const char* cshaderfunction);
extern void InsertShaderFunction(const char* cfilename, const char* cshaderfunction);
// loading data from shader collection.
/*
	// Load Shader File
*/
extern Boolean LoadShaderFileFromCollection(const char* cfilename, const char* funcname,ShaderFileHeader** header);
// Load shader file by Index
extern Boolean LoadShaderFileFromCollectioni(const char* cfilename, unsigned int index,ShaderFileHeader** header);
/*
	// Load Shader function 
*/
extern void LoadShaderFunci(const char* cfilename, unsigned int index,char** cfunc);
extern void LoadShaderFuncs(const char* cfilename, const char* func_name,char** cfunc);
/*
	// load list of all shader file name
*/
extern void LoadShaderNameList(const char* cfilename, struct shader_name_list* list);

/*
	// explict shader element from shader file	
	// Remark: it won't create buffer. instead only references of the shaderfile.
*/
extern void GetShaderFileElements(const ShaderFileHeader* shaderfile,char** cname,char** _Str_vertex_source, char** _Str_fragment_source, char** _Str_geometry_source, char** _Str_tesselation_control_source, char** _Str_tesselation_evolution_source);
/*
	// get shader file element by flag
*/
extern char* GetShaderFileElement(const ShaderFileHeader* shaderfile, unsigned int iflag);
/*
	// encrypt shader collection
*/
extern Boolean EncryptShaderCollection(const char* cfilename);
/*
	// encrypt shaderfile
*/
extern Boolean EncryptShaderFile(ShaderFileHeader* shaderfile);

extern Boolean DecryptShaderCollection(const char* cfilename);
extern Boolean DecryptShaderFile(ShaderFileHeader* shaderfile);

#ifdef __cplusplus // C++ environment
}
#endif

#endif