/// \file Condorcet.c
/// \author Anthony PAILLA
/// \date decembre 2021

#include "Condorcet.h"

int **Condorcet(MonTableau *tabtab){
/// \fn fonction Condorcet
/// \param[in] structure Montableau
/// \return Matrice de duel
/// \brief transforme un ballot en matrice de duel
    int **MDuel = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol);
    for (int i =0;i<tabtab->nbcol;i++){ //double for pour initialiser la matrice de duel à 0
        for (int j=0;j<tabtab->nbcol;j++){
            MDuel[j][i]=0;
        }
    }
    for (int indexvotant=0; indexvotant<tabtab->nblignes; indexvotant++){
        for (int candidatA=0; candidatA<tabtab->nbcol-1; candidatA++){
            for (int candidatB=candidatA+1; candidatB<tabtab->nbcol;candidatB++){
                MDuel[candidatA][candidatB]+=(tabtab->tab[indexvotant][candidatA]<tabtab->tab[indexvotant][candidatB]); //ajoute +1 dans la matrice de duel quand A bat B
                MDuel[candidatB][candidatA]+=(tabtab->tab[indexvotant][candidatB]<tabtab->tab[indexvotant][candidatA]); //ajoute +1 dans la matrice de duel quand 1 bat B
            }
        }
    }
    return MDuel;
}

void Schulze(MonTableau *tabtab,bool o, FILE * log){
/// \fn fonction schulze
/// \param[in] structure Montableau
/// \brief recherche le chemin le plus fort
    if (o) fprintf(log,"||||||||| mode de scrutin : Condorcet Schulze |||||||||\n");
    int **MDuel = Condorcet(tabtab); //recuperation de la matrice de duel
    int **MResult = createDynamiqueTab2D(tabtab->nbcol,tabtab->nbcol); //initialisation de la matrice des chemins
    int *MCandidats = createDynamiqueTab1D(tabtab->nbcol); //nb de meilleurs chemins
    int score,id_gagnant;
    if (o) fprintf(log,"\nmatrice Duel:\n");
    if (o) afficherTab2D(MDuel,tabtab->nbcol,tabtab->nbcol,log);
    for (int i=0; i<tabtab->nbcol; i++){
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j){
                if(MDuel[i][j]>MDuel[j][i]){
                    MResult[i][j]=MDuel[i][j]; //matrice de combien i perd contre j
                }else{
                    MResult[i][j]=0; //sinon 0
                }
            }else{
                MResult[i][j]=0;
            }
        }
    }

    if (o) fprintf(log,"\nmatrice chemin:\n");
    if (o) afficherTab2D(MResult,tabtab->nbcol,tabtab->nbcol,log);
    for (int i=0; i<tabtab->nbcol; i++){
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j){
                for(int k=0; k<tabtab->nbcol; k++){
                    if (i!=k && j!=k){
                        MResult[j][k]= fmax((double)MResult[j][k],fmin((double)MResult[j][i],(double)MResult[i][k])); //creation du chemin le plus fort du candidat j au candidat k
                    }
                }
            }
        }
    }

    for (int i = 0; i < tabtab->nbcol; i++) {
        MCandidats[i]= 0;
        for (int j=0 ; j<tabtab->nbcol; j++){
            if (i!=j) {
                MCandidats[i] += MResult[i][j] > MResult[j][i]; //compte le nombre de chemin le plus fort
            }
        }
    }

    if (o) fprintf(log,"\nliste nombre chemin plus fort:\n");
    if (o) afficherTab1D(MCandidats,tabtab->nbcol,log);
    id_gagnant=max_tab(MCandidats,tabtab->nbcol,&score,-1); //recupere le maximum du nombre de chemin
    printf("\nmode de scrutin : Condorcet Schulze, %d candidats, %d votants, vainqueur = %s\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    if (o) fprintf(log,"\n%d candidats, %d votants, vainqueur = %s\n\n",
            tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);

    destroyDynamiqueTab2D(MDuel,tabtab->nbcol);
    destroyDynamiqueTab2D(MResult,tabtab->nbcol);
    destroyDynamiqueTab1D(MCandidats); //free les tableaux
}

void Minimax(MonTableau *tabtab, bool o, FILE * log){
/// \fn fonction minimax
/// \param[in] structure Montableau
/// \brief sort le maximum des minimun d'une matrice de duel
    if (o) fprintf(log,"||||||||| mode de scrutin : Condorcet Minimax |||||||||\n");
    int **MDuel = Condorcet(tabtab); //recuperation de la matrice de duel
    int **MResult = createDynamiqueTab2D(tabtab->nbcol, tabtab->nbcol); //initialisation de la matrice des chemins
    int *MCandidats = createDynamiqueTab1D(tabtab->nbcol); //nb de meilleurs chemins
    int score,id_gagnant;
    if (o) fprintf(log,"\nmatrice Duel:\n");
    if (o) afficherTab2D(MDuel,tabtab->nbcol,tabtab->nbcol,log);

    for (int i = 0; i < tabtab->nbcol; i++) {
        for (int j = 0; j < tabtab->nbcol; j++) {
            MResult[i][j] = MDuel[i][j] - MDuel[j][i]; //de combien i gagne contre j
        }
    }

    if (o) fprintf(log,"\nmatrice chemin:\n");
    if (o) afficherTab2D(MResult,tabtab->nbcol,tabtab->nbcol,log);
    for (int i = 0; i < tabtab->nbcol; i++) { //recherche des chemins minimum
        min_tab(MResult[i], tabtab->nbcol, &score, i);
        MCandidats[i] = score;
    }

    if (o) fprintf(log,"\nliste nombre pires chemins:\n");
    if (o) afficherTab1D(MCandidats,tabtab->nbcol,log);
    id_gagnant=max_tab(MCandidats,tabtab->nbcol,&score,-1); //recherche le maximum des chemins minimum

    printf("\nmode de scrutin : Condorcet Minimax, %d candidats, %d votants, vainqueur = %s\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    if (o) fprintf(log,"\n%d candidats, %d votants, vainqueur = %s\n\n",
            tabtab->nbcol,tabtab->nblignes,tabtab->tabName[id_gagnant]);
    destroyDynamiqueTab2D(MDuel,tabtab->nbcol);
    destroyDynamiqueTab2D(MResult,tabtab->nbcol);
    destroyDynamiqueTab1D(MCandidats); //free les tableaux
}
