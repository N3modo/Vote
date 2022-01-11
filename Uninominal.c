/// \file Uninominal.c
/// \author Anthony PAILLA
/// \date november 2021
#include "Uninominal.h"

void uninominale1(MonTableau *tabtab, bool o, FILE * log){
/// \fonction uninominale a 1 tour
/// \param[in] structure MonTableau
/// \brief fait une vote par classement en un tour
    if (o) fprintf(log,"||||||||| mode de scrutin : uninominal a un tour |||||||||\n");
    int leGagnant,leGagnant2,sasuke,score_gagnant,score2;
    int *tableau_participant = createDynamiqueTab1D(tabtab->nbcol);
    for (int i=0; i<tabtab->nblignes; i++){ //ajout nb de vote dans tableau au indice des candidats
        sasuke = min_tab(tabtab->tab[i],tabtab->nbcol,&score_gagnant,-1);
        if (sasuke != -1) tableau_participant[sasuke]++;
    }

    if (o) afficherTab1D(tableau_participant,tabtab->nbcol,log);
    leGagnant = max_tab(tableau_participant,tabtab->nbcol, &score_gagnant, -1);
    //printf("\ngagnant 1 : %s \n",tabtab->tabName[leGagnant]);
    if (o) fprintf(log,"\ngagnant 1 : %s \n",tabtab->tabName[leGagnant]);
    leGagnant2 = max_tab(tableau_participant,tabtab->nbcol, &score2, leGagnant);
    //printf("\ngagnant 2 : %s \n",tabtab->tabName[leGagnant2]);
    if (o) fprintf(log,"gagnant 2 : %s \n",tabtab->tabName[leGagnant2]);
    destroyDynamiqueTab1D(tableau_participant);
    if (score2==score_gagnant) {
        printf("\nmode de scrutin : uninominal a un tour : egalité entre %s et %s\n",
               tabtab->tabName[leGagnant],tabtab->tabName[leGagnant2]);
        return;
    }
    printf("\nmode de scrutin : uninominal a un tour, %d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[leGagnant],(float)score_gagnant*100/(float)tabtab->nblignes);
    if (o) fprintf(log,"\n%d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
            tabtab->nbcol,tabtab->nblignes,tabtab->tabName[leGagnant],(float)score_gagnant*100/(float)tabtab->nblignes);
}

void uninominale2(MonTableau *tabtab, bool o, FILE * log){
/// \fonction uninominale a 2 tour
/// \param[in] structure MonTableau
/// \brief fait une vote par classement en deux tour
    if (o) fprintf(log,"\n||||||||| Mode de scrutin : uninominal a deux tour |||||||||\n");
    int gagnant1,gagnant2,sasuke,nbvote,nbvote2;
    int *tableau_participant = createDynamiqueTab1D(tabtab->nbcol);
    for (int i=0; i<tabtab->nblignes; i++){ //ajout nb de vote dans tableau au indice des candidats
        sasuke = min_tab(tabtab->tab[i],tabtab->nbcol,&nbvote,-1);
        if (sasuke != -1) tableau_participant[sasuke]++;
    }

    if (o) afficherTab1D(tableau_participant,tabtab->nbcol,log);
    gagnant1 = max_tab(tableau_participant,tabtab->nbcol, &nbvote, -1); //1e gagnant de uni2 tour 1
    if (o) fprintf(log,"\ngagnant 1 : %s, score = %.2f %% \n",tabtab->tabName[gagnant1],(float)(nbvote*100)/(float)tabtab->nblignes);
    printf("\nmode de scrutin : uninominal a deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[gagnant1], (float)(nbvote*100)/(float)tabtab->nblignes); //1er gagnant de uni2

    if(nbvote > tabtab->nblignes/2) return;
    gagnant2 = max_tab(tableau_participant,tabtab->nbcol, &nbvote, gagnant1); //2e gagnant de uni2 tour 1
    if (o) fprintf(log,"\ngagnant 2 : %s, score = %.2f %% \n",tabtab->tabName[gagnant2],(float)(nbvote*100)/(float)tabtab->nblignes);
    printf("mode de scrutin : uninominal a deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nbcol,tabtab->nblignes,tabtab->tabName[gagnant2],(float)(nbvote*100)/(float)tabtab->nblignes); //2e gagnant de uni2
    destroyDynamiqueTab1D(tableau_participant);

    nbvote=0;
    nbvote2=0;
    for (int i=0; i<tabtab->nblignes; i++) {
        if (tabtab->tab[i][gagnant1] < tabtab->tab[i][gagnant2])nbvote++;  //nb de vote gagnant 2 tour 2
        if (tabtab->tab[i][gagnant1] > tabtab->tab[i][gagnant2])nbvote2++;  //nb de vote gagnant 1 tour 2
    }
    if (o) fprintf(log,"\nnombre de vote candidat 1 : %d ",nbvote);
    if (o) fprintf(log,"\nnombre de vote candidat 2 : %d ",nbvote2);

    if (nbvote == nbvote2){
        printf("mode de scrutin : uninominal a deux tours, tour 2, 2 candidats, %d votants, egalité entre %s et %s, score = %.2f %%\n",
               tabtab->nblignes,tabtab->tabName[gagnant1],tabtab->tabName[gagnant2],(float)(nbvote*100)/(float)tabtab->nblignes);
        if (o) fprintf(log,"\ntour 2, 2 candidats, %d votants, egalité entre %s et %s, score = %.2f %%\n",
                tabtab->nblignes,tabtab->tabName[gagnant1],tabtab->tabName[gagnant2],(float)(nbvote*100)/(float)tabtab->nblignes);
    }
    printf("mode de scrutin : uninominal a deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
           tabtab->nblignes,tabtab->tabName[nbvote>nbvote2 ? gagnant1 : gagnant2],(float)((nbvote>nbvote2 ? nbvote : nbvote2)*100)/(float)tabtab->nblignes); //gagnant final
    if (o) fprintf(log,"\ntour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2f %%\n",
            tabtab->nblignes,tabtab->tabName[nbvote>nbvote2 ? gagnant1 : gagnant2],(float)((nbvote>nbvote2 ? nbvote : nbvote2)*100)/(float)tabtab->nblignes); //gagnant final
}
