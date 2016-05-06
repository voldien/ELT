#include"elt_endian.h"


void ExSwap16(Uint16 x){
	EX_ASM("xchg %b0,%h0": "=q"(x):"0"(x));
}

void ExSwap32(Uint32 x){
	EX_ASM("BSWAP %0": "=r"(x):"0"(x));
}

