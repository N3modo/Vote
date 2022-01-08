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
    return **MDuel;
}

int Schulze(MonTableau *tabtab,int **MDuel,int NbCandidat){
    int **MResult = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol);
    for (int i=0; i<NbCandidat; i++){
        for (int j=0 ; j<NbCandidat; j++){
            if (i!=j){
                if(MDuel[i][j]>MDuel[j][i]){
                    MResult[i][j]=MDuel[i][j];
                }else{
                    MResult[i][j]=0;
                }
            }
        }
    }
    for (int i=0; i<NbCandidat; i++){
        for (int j=0 ; j<NbCandidat; j++){
            if (i!=j){
                for(int k=0; k<NbCandidat; k++){
                    if (i!=k && j!=k){
                        MResult[j][k]= max(MResult[j][k],min(MResult[j][i],MResult[i][k]));
                    }
                }
            }
        }
    }
    return **MResult;
}

int Minimax(){
    return 0;
}
int maxDuel(int *max){
    *max=0;
    int position=0;
    return position;
}