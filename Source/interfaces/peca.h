#pragma once

typedef struct peca* PecaHead;

typedef enum{
	PEC_notEnoughMemory = -1,
	PEC_ok = 0,
	PEC_doNotExist = 1,
	PEC_colorNotExist = 2,
	PEC_alreadyExists = 3
} PEC_CondRet;

typedef enum{
	COLOR_Black = 0,
	COLOR_White = 1
}Color;

PEC_CondRet PEC_createPeca(Color color, PecaHead* ret);

PEC_CondRet PEC_getColor(Color *ret, PecaHead p);
