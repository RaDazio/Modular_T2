#pragma once

#include "peca.h"

void RenderizarTabuleiro();

void LimparRender();

void RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas, int pode_dobrar);

void Menu(int* resposta);