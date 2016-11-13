#include"elt_endian.h"

/*	TODO perhaps relocate to the header.	*/

void ExSwap16(unsigned short x){
#ifdef EX_X86
	EX_ASM("xchg %b0,%h0": "=q"(x):"0"(x));
#endif
}

void ExSwap32(unsigned int x){
#ifdef EX_X86
	EX_ASM("BSWAP %0": "=r"(x):"0"(x));
#endif
}

