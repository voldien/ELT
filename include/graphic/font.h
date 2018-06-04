/**
	ELT (Engine Library Toolkit) is a cross platform engine toolkit
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
#ifndef _ELT_FONT_H_
#define _ELT_FONT_H_
#include"./../elt_def.h"

struct ex_font_coordination {
	int x;
	int y;
	int width;
	int height;
};

struct ex_font_location {
	unsigned int num;
	struct ex_font_coordination coordination;
};

typedef struct ex_font_t {
	unsigned int font_texture; /*TODO make it to a pointer	*/
	unsigned int texWidth;
	unsigned int texHeight;
	unsigned int texBpp;
	float pt;
	float advance[128];
	float width[128];
	float height[128];
	float tex_x1[128];
	float tex_x2[128];
	float tex_y1[128];
	float tex_y2[128];
	float offset_x[128];
	float offset_y[128];
} ExFont;

/*
 *
 *	@Return
 */
extern ELTDECLSPEC ExFont* ELTAPIENTRY ExCreateFont(const char* cfilename,
		int pointSize, int dpi, unsigned int flag);

/*
 *
 *	@Return
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExDeleteFont(ExFont* font);

#endif
