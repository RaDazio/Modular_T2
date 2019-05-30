#define TABSIZE 24
#define MAXPERCASA 15

#include <stdio.h>
#include <Windows.h>

#include "..\interfaces\user_interface.h"
#include "..\interfaces\tabuleiro.h"
#include "..\interfaces\peca.h"
#include "..\interfaces\lista.h"


void RenderizarTabuleiro();

void LimparRender();

void RenderizarTabuleiro(){
	LIS_tppLista casas;
	TBL_CondRet cond = TBL_ObterCasas(&casas);
	int idx;
	if(cond == TBL_tabNaoExiste) exit(1);
	IrInicioLista(casas);
	
	system("mode 800");
	system("cls");
	printf("\n");
	for(idx = 1 ; LIS_AvancarElementoCorrente(casas, 1) != LIS_CondRetFimLista || idx <= TABSIZE; idx++){
		printf("  | %2d |", idx);
		if(idx == TABSIZE/2){
			int i;
			printf("|\n");
			for(i = 0; i < MAXPERCASA*2; i++){
				printf("  |%93s|\n"," ");
			}
		}
	}
	printf("|\n");

	return;
}
