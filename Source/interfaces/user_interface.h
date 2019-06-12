#pragma once

#include "peca.h"

void RenderizarTabuleiro(int pontuacao_preta, int pontuacao_branca);

void LimparRender();

void RenderizarJogadaAtual(PEC_color jogadorAtual, int dices[4], int qtd_dice_valid, int vector[24], int qtd_casas);

void Menu_Inicial(int* resposta);

void Menu_Sair(int *resposta);

void RenderizarMenuDePontos(int *response, PEC_color jogador_da_vez);
