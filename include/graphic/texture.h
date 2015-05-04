/**
    ELT (Engine Library Toolkit) is a multi platform engine toolkit
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _ELT_TEXTURE_H_ 
#define _ELT_TEXTURE_H_ 1

#ifdef __cplusplus	/* C++ environment	*/
extern "C"{
#endif 

/**
	// return texture internal type in size in bytes
*/
extern unsigned int get_texture_type_size(unsigned int internalformat);
/**
	// Get texture Internal format by number of bits
*/
extern unsigned int get_texture_size_type(unsigned int bitsperPixel);
/**

*/
extern unsigned int get_internal_srgb_type(unsigned int internal_format);

/*
	// get texture size in bytes
*/
extern unsigned int get_texture_data_size(unsigned int textureid);
/**
    Get texture data by level in unsigned int
*/
extern unsigned int get_texture_level_datai(unsigned int textureid,unsigned int level,unsigned char** pixeldata);
/**
    Get texture data by level in floating number
*/

extern unsigned int get_texture_level_dataf(unsigned int textureid,unsigned int level,float** pixeldata);

extern unsigned int create_texture(unsigned char* pixeldata,unsigned int width, unsigned int height);


extern float get_max_texture_anisotropy(void);
extern void  set_texture_anisotropy(float anisotropy);


//GL_NUM_COMPRESSED_TEXTURE_FORMATS
extern int get_num_texture_compress_format(void);



#ifdef __cplusplus	/* C++ environment	*/
}
#endif 


#endif 

