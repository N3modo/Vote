/// \file Condorcet.h
/// \author Anthony PAILLA
/// \date decembre 2021

#ifndef TEST_VOTE_CONDORCET_H
#define TEST_VOTE_CONDORCET_H

#include "Main.h"

int **Condorcet(MonTableau *tabtab);
void Schulze(MonTableau *tabtab);
void Minimax(MonTableau *tabtab);

#endif //TEST_VOTE_CONDORCET_H
