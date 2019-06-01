#include <stdio.h>
#include <Windows.h>

#include "interfaces\dado.h"

#include "interfaces\peca.h"
#include "interfaces\tabuleiro.h"
#include "interfaces\user_interface.h"

#define DADOS_LADOS 6


int dices[2];

void setUp (){
	system("echo off");	
	system("mode 800");
	system("color 70");

	TBL_CriarTabuleiro();
}


int main (void){
	setUp();
	RenderizarTabuleiro();
	TBL_MoverPeca(12,15);
	system("timeout 5");
	RenderizarTabuleiro();

	return 0;
}