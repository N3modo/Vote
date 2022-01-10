/// \file Condorcet.h
/// \author Anthony PAILLA
/// \date decembre 2021

#ifndef Condorcet_h
#define Condorcet_h

#include "Main.h"

int **Condorcet(MonTableau *tabtab);
void Schulze(MonTableau *tabtab, bool o, FILE * log);
void Minimax(MonTableau *tabtab, bool o, FILE * log);

#endif
