#pragma once

#include "peca.h"

void RenderizarTabuleiro();

void LimparRender();

void RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[2], int casasPossiveis[], int n_casas_possiveis, int pode_dobrar);