#pragma once

#include "peca.h"

void RenderizarTabuleiro();

void LimparRender();

void RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[2], int vector[24], int qtd_casas, int pode_dobrar);