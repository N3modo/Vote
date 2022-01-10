/// \file Uninominal.c
/// \author Anthony PAILLA
/// \date november 2021
#include "Uninominal.h"

void uninominale1(MonTableau *tabtab){
/// \fonction uninominale a 1 tour
/// \param[in] structure MonTableau
    int leGagnant,leGagnant2,sasuke,score_gagnant,score2;
    int *tableau_participant = createDynamiqueTab1D(tabtab->nbcol);
    for (int i=0; i<tabtab->nblignes; i++){ /// \brief ajout nb de vote dans tableau au indice des candidats
        sasuke = min_tab(tabtab->tab[i],tabtab->nbcol,&score_gagnant,-1);
        if (sasuke != -1) tableau_participant[sasuke]++;
    }
    leGagnant = max_tab(tableau_participant,tabtab->nbcol, &score_gagnant, -1);
    leGagnant2 = max_tab(tableau_participant,tabtab->nbcol, &score2, leGagnant);
    destroyDynamiqueTab1D(tableau_participant);
    if (score2==score_gagnant) {
        printf("\nmode de scrutin : uninominal a un tour : egalité entre %s et %s\n",
               tabtab->tabName[leGagnant],tabtab->tabName[leGagnant2]);
        return;
    }
    printf("\nmode de scrutin : uninominal a un tour, %d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[leGagnant],(float)score_gagnant*100/(float)tabtab->nblignes);
}

void uninominale2(MonTableau *tabtab){
/// \fonction uninominale a 2 tour
/// \param[in] structure MonTableau
    int gagnant1,gagnant2,sasuke,nbvote,nbvote2;
    int *tableau_participant = createDynamiqueTab1D(tabtab->nbcol);
    for (int i=0; i<tabtab->nblignes; i++){ /// \brief ajout nb de vote dans tableau au indice des candidats
        sasuke = min_tab(tabtab->tab[i],tabtab->nbcol,&nbvote,-1);
        if (sasuke != -1) tableau_participant[sasuke]++;
    }
    gagnant1 = max_tab(tableau_participant,tabtab->nbcol, &nbvote, -1); /// \brief 1e gagnant de uni2 tour 1
    printf("\nmode de scrutin : uninominal a deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",tabtab->nbcol,tabtab->nblignes,tabtab->tabName[gagnant1], (float)(nbvote*100)/(float)tabtab->nblignes); /// \1er gagnant de uni2
    if(nbvote > tabtab->nblignes/2) return;
    gagnant2 = max_tab(tableau_participant,tabtab->nbcol, &nbvote, gagnant1); /// \brief 2e gagnant de uni2 tour 1
    printf("mode de scrutin : uninominal a deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[gagnant2],(float)(nbvote*100)/(float)tabtab->nblignes); /// \brief 2e gagnant de uni2
    destroyDynamiqueTab1D(tableau_participant);
    nbvote=0;
    nbvote2=0;
    for (int i=0; i<tabtab->nblignes; i++) {
        if (tabtab->tab[i][gagnant1] < tabtab->tab[i][gagnant2])nbvote++;  /// \brief nb de vote gagnant 2 tour 2
        if (tabtab->tab[i][gagnant1] > tabtab->tab[i][gagnant2])nbvote2++;  /// \brief nb de vote gagnant 1 tour 2
    }
    if (nbvote == nbvote2){
        printf("mode de scrutin : uninominal a deux tours, tour 2, 2 candidats, %d votants, egalité entre %s et %s, score = %.2f %%\n",
               tabtab->nblignes,tabtab->tabName[gagnant1],tabtab->tabName[gagnant2],(float)(nbvote*100)/(float)tabtab->nblignes);
    }
    printf("mode de scrutin : uninominal a deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nblignes,tabtab->tabName[nbvote>nbvote2 ? gagnant1 : gagnant2],(float)((nbvote>nbvote2 ? nbvote : nbvote2)*100)/(float)tabtab->nblignes); /// \brief gagnant
}
