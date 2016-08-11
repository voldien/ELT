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
#ifndef _ELT_ALLOC_H_
#define _ELT_ALLOC_H_ 1
#include"system.h"

#ifdef  __cplusplus	/* C++ Environment */
extern "C"{
#endif

/**
 *	Get Page size.
 *	@Return number of bytes per page.
 */
extern ELTDECLSPEC Uint ELTAPIENTRY ExGetPageSize(void);


/**
 *	Get total system memory on the system.
 *	@Return
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalSystemMemory(void);

/**
 *
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalFreeSystemMemory(void);

/**
 *
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalUsedSystemMemory(void);

/**
 *
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetProcessSystemMemory(void);


/*
 *	Get total virtual memory on the system.
 *	@Return
 */
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalVirtualMemory(void);
extern ELTDECLSPEC Uint64 ELTAPIENTRY ExGetTotalUsedVirtualMemory(void);





/*	TODO move to a header with data structure!	*/
typedef struct ex_pool_allocator{
	void* next;
}ExPoolAllocator;

/**
 *	Poll allocator
 *	@Return
 */
extern ELTDECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolCreate(unsigned int num, unsigned int itemsize);

/**
 *	obtain next item
 *	If return value is null, then the allocator
 *	is full
 *	@Return
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExPoolObtain(ExPoolAllocator* allactor);

/**
 *	@Return current next.
 */
extern ELTDECLSPEC void* ELTAPIENTRY ExPoolReturn(ExPoolAllocator* allactor, void* data);

/**
 *	@Return
 */
extern ELTDECLSPEC ExPoolAllocator* ELTAPIENTRY ExPoolResize(ExPoolAllocator* allcotor, unsigned num, unsigned int itemsize);

/**
 *
 */
extern ELTDECLSPEC void ELTAPIENTRY ExPoolFree(ExPoolAllocator* allactor);

/**
 *	Get data pointer at index.
 */
#define ExPoolIndex(alloc, index, len)	( ( alloc ) + (( index ) * ( len )  + ( index )) )

/**
 *
 */
#define ExPoolDataIndex(alloc, data, len)	((data - alloc)




EX_ALIGN_PREFIX(4)
typedef struct ex_list{
	/*
	 *
	 */
	struct ex_list* next;

	/*
	 *
	 */
	struct ex_list* previous;


}ExList;

/**
 *	Create double linked list.
 */
extern ELTDECLSPEC ExList* ExCreateList(ExList* list, unsigned int num, unsigned int itemsize);

/**
 *
 */
extern ELTDECLSPEC ExList* ExCreateListS(ExList* list, unsigned int num, unsigned int itemsize);





EX_ALIGN_PREFIX(4)
typedef struct ex_quad_tree{
	struct ex_quad_tree* t0;
	struct ex_quad_tree* t1;
	struct ex_quad_tree* t2;
	struct ex_quad_tree* t3;
	void* data[0];
}ExQuadTree;


/**/
extern ELTDECLSPEC ExQuadTree* ExCreateQuadTree(ExQuadTree* list, unsigned int depth, unsigned int itemsize);




EX_ALIGN_PREFIX(4)
typedef struct ex_octree_tree{
	struct ex_octree_tree* t0[8];
}ExOctreTree;

/**/
extern ELTDECLSPEC ExQuadTree* ExCreateOcTree(ExList* list, unsigned int depth, unsigned int itemsize);



typedef struct ex_hash_table{
	unsigned int num;

}ExHashTable;

/**/
extern ELTDECLSPEC ExQuadTree* ExCreateHashTable(ExList* list, unsigned int depth, unsigned int itemsize);

#ifdef __cplusplus
}
#endif

#endif
