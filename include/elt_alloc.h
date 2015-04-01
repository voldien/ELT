/**
========================================================================
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
#ifndef _ELT_ALLOC_H_
#define _ELT_ALLOC_H_ 1
#include"EngineAssembly.h"

#define DATABLOCK 0x1000    // 4096 // 4 kbyte
#define ExMallocBlock(size) (malloc((( ( size ) / DATABLOCK) + 1) * DATABLOCK))
#define ExMalloc malloc
#define ExCalloc calloc
#define ExReAlloc realloc
#define ExFree(p_pointer) {free(p_pointer);p_pointer = EX_NULL;}

struct datablock{
    void* pointer;
    unsigned int size;
    unsigned int position;
};
/**
    Get Page size
    @return number of bytes per page.
*/
extern DECLSPEC int ELTAPIENTRY ExGetPageSize(void);

extern DECLSPEC int ELTAPIENTRY ExAllocBlock(unsigned int size);



#endif // _ELT_ALLOC_H
