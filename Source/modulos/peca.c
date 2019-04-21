#include "../interfaces/peca.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct peca Peca;

struct peca{
	Color color;
};

PEC_CondRet PEC_createPeca(Color color, PecaHead* ret){
	*ret = (PecaHead)malloc(sizeof(PecaHead));
	if(*ret == NULL) return PEC_notEnoughMemory;
	if(color != COLOR_White && color != COLOR_Black) return PEC_colorNotExist;
	(*ret)->color = color;
	return PEC_ok;
}

PEC_CondRet PEC_getColor(Color *ret, PecaHead p){
	if( p == NULL ) return PEC_doNotExist;
	*ret = p->color;
	return PEC_ok;
}

