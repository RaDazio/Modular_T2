#include <stdio.h>
#include <Windows.h>

#include "interfaces\dado.h"

#include "interfaces\peca.h"
#include "interfaces\tabuleiro.h"
#include "interfaces\user_interface.h"

#define DADOS_LADOS 6


int dices[2];




int main (void){
	TBL_CriarTabuleiro();
	RenderizarTabuleiro();
	TBL_MoverPeca(0,5);
	system("timeout 5");
	RenderizarTabuleiro();





	return 0;
}