/// \file debut.h
/// \author Anthony PAILLA
/// \date november 2021

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
char** createDynamiqueStringTab2D(int ligne,int nbcolonne);/*
void tab1d_in_struct(?);
void tab2d_in_struct(?);
void tab2dstring_in_struct(?);*/
MonTableau read_csv(char *filename, int offsetLigne, int offsetCol);
