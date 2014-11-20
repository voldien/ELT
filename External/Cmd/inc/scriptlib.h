/*
===========================================================================
Copyright (C) 2014 BroodCity Software, Inc. Voldemor2009@hotmail.com

*/
#ifndef SCRIPT_LIB_H
#define SCRIPT_LIB_H
#ifndef STRING_LIB_H
	#include"stringlib.h"
#endif
#ifndef CMD_LIB_H
	#include"cmdlib.h"
#endif
#ifdef __cplusplus
extern "C"{
#endif
/*
	// compiler string function
*/
int get_function_name(const char* _str, int pos, int ilength);
int get_function_paramter_count(const char* _Str, const char* copening,int pos);
int get_function_comment_pos(const char* _Str, int pos, int ilength);
int remove_comment(const char* _Str, int pos,int ilength);
Boolean is_script_pos_comment(const char* _str, int pos);

#ifdef __cplusplus
}
#endif
#endif