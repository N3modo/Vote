/// \file Condorcet.c
/// \author Anthony PAILLA
/// \date decembre 2021

#include "Condorcet.h"

int **Condorcet(MonTableau *tabtab){
/// \fn fonction Condorcet : transforme un ballot en matrice de duel
/// \param[in] structure Montableau
/// \return Matrice de duel
    int **MDuel = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol);
    for (int i =0;i<tabtab->nbcol;i++){ /// \ double for pour initialiser la matrice de duel à 0
        for (int j=0;j<tabtab->nbcol;j++){
            MDuel[j][i]=0;
        }
    }
    for (int indexvotant=0; indexvotant<tabtab->nblignes; indexvotant++){
        for (int candidatA=0; candidatA<tabtab->nbcol-1; candidatA++){
            for (int candidatB=candidatA+1; candidatB<tabtab->nbcol;candidatB++){
                MDuel[candidatA][candidatB]+=(tabtab->tab[indexvotant][candidatA]<tabtab->tab[indexvotant][candidatB]); /// \ajoute +1 dans la matrice de duel quand A bat B
                MDuel[candidatB][candidatA]+=(tabtab->tab[indexvotant][candidatB]<tabtab->tab[indexvotant][candidatA]); /// \ajoute +1 dans la matrice de duel quand 1 bat B
            }
        }
    }
    return MDuel;
}

void Schulze(MonTableau *tabtab){
/// \fn fonction schulze
/// \param[in] structure Montableau
    int **MDuel = Condorcet(tabtab); /// \brief recuperation de la matrice de duel
    int **MResult = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol); /// \brief initialisation de la matrice des chemins
    int *MCandidats = createDynamiqueTab1D(tabtab->nbcol); /// \brief nb de meilleurs chemins
    int score,id_gagnant;
    for (int i=0; i<tabtab->nbcol; i++){
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j){
                if(MDuel[i][j]>MDuel[j][i]){
                    MResult[i][j]=MDuel[i][j]; /// \brief matrice de combien i perd contre j
                }else{
                    MResult[i][j]=0; /// \brief sinon 0
                }
            }
        }
    }
    for (int i=0; i<tabtab->nbcol; i++){
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j){
                for(int k=0; k<tabtab->nbcol; k++){
                    if (i!=k && j!=k){
                        MResult[j][k]= fmax((double)MResult[j][k],fmin((double)MResult[j][i],(double)MResult[i][k])); /// \brief creation du chemin le plus fort du candidat j au candidat k
                    }
                }
            }
        }
    }
    for (int i = 0; i < tabtab->nbcol; i++) {
        MCandidats[i]= 0;
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j) {
                MCandidats[i] += MResult[i][j] > MResult[j][i]; /// \brief compte le nombre de chemin le plus fort
            }
        }
    }
    id_gagnant=max_tab(MCandidats,tabtab->nbcol,&score,-1); /// \brief recupere le maximum du nombre de chemin
    printf("\nmode de scrutin : Condorcet Schulze, %d candidats, %d votants, vainqueur = %s\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    destroyDynamiqueTab2D(MDuel,tabtab->nbcol);
    destroyDynamiqueTab2D(MResult,tabtab->nbcol);
    destroyDynamiqueTab1D(MCandidats); /// \brief free les tableaux
}

void Minimax(MonTableau *tabtab){
/// \fn fonction minimax
/// \param[in] structure Montableau
    int **MDuel = Condorcet(tabtab); /// \brief recuperation de la matrice de duel
    int **MResult = createDynamiqueTab2D(tabtab->nbcol, tabtab->nbcol); /// \brief initialisation de la matrice des chemins
    int *MCandidats = createDynamiqueTab1D(tabtab->nbcol); /// \brief nb de meilleurs chemins
    int score,id_gagnant;
    for (int i = 0; i < tabtab->nbcol; i++) {
        for (int j = 0; j < tabtab->nbcol; j++) {
            MResult[i][j] = MDuel[i][j] - MDuel[j][i]; /// \brief de combien i gagne contre j
        }
    }
    for (int i = 0; i < tabtab->nbcol; i++) { /// \brief recherche des chemins minimum
        min_tab(MResult[i], tabtab->nbcol, &score, i);
        MCandidats[i] = score;
    }
    id_gagnant=max_tab(MCandidats,tabtab->nbcol,&score,-1); /// \brief recherhce le maximum des chemins minimum
    printf("\nmode de scrutin : Condorcet Minimax, %d candidats, %d votants, vainqueur = %s\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    destroyDynamiqueTab2D(MDuel,tabtab->nbcol);
    destroyDynamiqueTab2D(MResult,tabtab->nbcol);
    destroyDynamiqueTab1D(MCandidats); /// \brief free les tableaux
}