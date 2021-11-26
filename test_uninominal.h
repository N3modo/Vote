/// \file debut.h
/// \author Anthony PAILLA
/// \date november 2021

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "debut.h"

int min_tab(int *tab, int taille);
int max_tab(int *tab, int taille, int* max, int excl);
int uninominale1(MonTableau *tabtab, int* max);
int uninominale2(MonTableau *tabtab);
