/// \file Condorcet.h
/// \author Anthony PAILLA
/// \date decembre 2021

#ifndef Condorcet_h
#define Condorcet_h

#include "Main.h"

int **Condorcet(MonTableau *tabtab);
void Schulze(MonTableau *tabtab,FILE * log);
void Minimax(MonTableau *tabtab,FILE * log);

#endif
