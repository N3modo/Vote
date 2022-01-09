/// \file Condorcet.c
/// \author Anthony PAILLA
/// \date decembre 2021

#include "Condorcet.h"

int **Condorcet(MonTableau *tabtab){
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

void Schulze(MonTableau *tabtab){
    int **MDuel = Condorcet(tabtab);
    int **MResult = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol);
    int *MCandidats = createDynamiqueTab1D(tabtab->nbcol); //nb de trucs verts
    int score,id_gagnant;
    for (int i=0; i<tabtab->nbcol; i++){
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j){
                if(MDuel[i][j]>MDuel[j][i]){
                    MResult[i][j]=MDuel[i][j]; // de combien i perd contre j
                }else{
                    MResult[i][j]=0; //
                }
            }
        }
    }
    for (int i=0; i<tabtab->nbcol; i++){
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j){
                for(int k=0; k<tabtab->nbcol; k++){
                    if (i!=k && j!=k){
                        MResult[j][k]= fmax((double)MResult[j][k],fmin((double)MResult[j][i],(double)MResult[i][k]));
                    }
                }
            }
        }
    }
    for (int i = 0; i < tabtab->nbcol; i++) {
        MCandidats[i]= 0;
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j) {
                MCandidats[i] += MResult[i][j] > MResult[j][i];
            }
        }
    }
    id_gagnant=max_tab(MCandidats,tabtab->nbcol,&score,-1);
    printf("\nmode de scrutin : Condorcet Schulze, %d candidats, %d votants, vainqueur = %s\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    destroyDynamiqueTab2D(MDuel,tabtab->nbcol);
    destroyDynamiqueTab2D(MResult,tabtab->nbcol);
    destroyDynamiqueTab1D(MCandidats);
}

void Minimax(MonTableau *tabtab){
    int **MDuel = Condorcet(tabtab);
    int **MResult = createDynamiqueTab2D(tabtab->nbcol, tabtab->nbcol);
    int *MCandidats = createDynamiqueTab1D(tabtab->nbcol);
    int score,id_gagnant;
    for (int i = 0; i < tabtab->nbcol; i++) {
        for (int j = 0; j < tabtab->nbcol; j++) {
            MResult[i][j] = MDuel[i][j] - MDuel[j][i]; // de combien i gagne contre j
        }
    }
    for (int i = 0; i < tabtab->nbcol; i++) {
        min_tab(MResult[i], tabtab->nbcol, &score, i);
        MCandidats[i] = score;
    }
    id_gagnant=max_tab(MCandidats,tabtab->nbcol,&score,-1);
    printf("\nmode de scrutin : Condorcet Minimax, %d candidats, %d votants, vainqueur = %s\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    destroyDynamiqueTab2D(MDuel,tabtab->nbcol);
    destroyDynamiqueTab2D(MResult,tabtab->nbcol);
    destroyDynamiqueTab1D(MCandidats);
}