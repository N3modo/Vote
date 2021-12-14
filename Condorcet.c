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


int main(int argc, char *argv[]) {}
/*
1.Create the different matrix and compute the total voting matrix
2. Check if there is an immediate Condorcet winner
     if yes, next miner is found
     Else continue
3. Check situation 1 (multiple rows with value > 0
     if yes, apply dictatorial choice = next miner is found
     Else continue
4. Apply Tideman procedure
     Next miner is found
    https://github.com/Perlkonig/Condorcet
    https://codes-sources.commentcamarche.net/source/53265-methode-de-vote-condorcet-sous-java
*/