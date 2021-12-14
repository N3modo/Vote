/// \file Condorcet.c
/// \author Anthony PAILLA
/// \date decembre 2021

#include "Condorcet.h"

int ballotToDuel(MonTableau *tabtab){
    int **MDuel = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol);
    for (int i =0;i<tabtab->nbcol;i++){
        for (int j=0;j<tabtab->nbcol;j++){
            MDuel[j][i]=0;
        }
    }
    for (int indexvotant=0; indexvotant<tabtab->nblignes; indexvotant++){
        for (int candidatA=0; candidatA<tabtab->nbcol-1; candidatA++){
            for (int candidatB=candidatA+1; candidatB<tabtab->nbcol;candidatB++){
                MDuel[candidatA][candidatB]+=(tabtab->tab[indexvotant][candidatA]<tabtab->tab[indexvotant][candidatB]);
                MDuel[candidatB][candidatA]+=(tabtab->tab[indexvotant][candidatB]<tabtab->tab[indexvotant][candidatA]);
            }
        }
    }
    return MDuel;
}

int minimax(){
    return 0
}


int maxDuel(int *max){
    *max=0;
    int position=0;
    return position;
}