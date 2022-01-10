/// \file utilitaires.h
/// \author Anthony PAILLA
/// \date decembre 2021

#ifndef utilitaires_h
#define utilitaires_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <math.h>

typedef struct {
    int nblignes;
    int nbcol;
    int **tab;
    char **tabName;
}MonTableau;

int* createDynamiqueTab1D(int ligne);
void destroyDynamiqueTab1D(int * tab);
int** createDynamiqueTab2D(int ligne,int nbcolonne);
void destroyDynamiqueTab2D(int ** tab, int ligne);
void ModifierTailleTableau(MonTableau *tab, int axe);
void InitTableau(MonTableau *tab);
void freeThemAll(MonTableau *tabtab);
void afficherTab(MonTableau *tab);
int min_tab(int *tab, int taille, int * min, int excl);
int max_tab(int *tab, int taille, int * max, int excl);
MonTableau read_csv(char *filename, int offsetLigne, int offsetCol);


#endif /// \utilitaires_h
