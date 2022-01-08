/// \file utilitaires.h
/// \author Anthony PAILLA
/// \date decembre 2021

#ifndef TEST_VOTE_UTILITAIRES_H
#define TEST_VOTE_UTILITAIRES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

typedef struct {
    int nblignes;
    int nbcol;
    int **tab;
    char **tabName;
}MonTableau;

int* createDynamiqueTab1D(int ligne);
int** createDynamiqueTab2D(int ligne,int nbcolonne);
char** createDynamiqueStringTab2D(int ligne,int nbcolonne);
void ModifierTailleTableau(MonTableau *tab, int axe);
void InitTableau(MonTableau *tab);
void freeThemAll(MonTableau *tabtab);
void afficherTab(MonTableau *tab);
MonTableau read_csv(char *filename, int offsetLigne, int offsetCol);


#endif //TEST_VOTE_UTILITAIRES_H
