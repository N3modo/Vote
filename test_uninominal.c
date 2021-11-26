#include "test_uninominal.h"

int min_tab(int *tab, int taille){
    for (int i=0; i<taille;i++){
        if (tab[i]==1){
            return i;
        }
    }
    return -1;
}

int max_tab(int *tab, int taille, int * max, int excl){
  *max=0;
  int position;
  for (int i=0; i<taille;i++){
    if ((tab[i]>=*max) && (i != excl)){
      *max=tab[i];
      position = i;
    }
  }
  return position;
}

int uninominale1(MonTableau *tabtab,int *max){
    int leGagnant,sasuke;
    int *tableau_participant = createDynamiqueTab1D(tabtab->nbcol);
    for (int i=0; i<tabtab->nblignes; i++){
        sasuke = min_tab(tabtab->tab[i],tabtab->nbcol);
        if (sasuke != -1) tableau_participant[sasuke]++;
    }
    leGagnant = max_tab(tableau_participant,tabtab->nbcol, max, -1);
    free(tableau_participant);
    return leGagnant;
}

int uninominale2(MonTableau *tabtab){
    int melenchon,zemmour,sasuke,max;
    int *tableau_participant = createDynamiqueTab1D(tabtab->nbcol);
    for (int i=0; i<tabtab->nblignes; i++){
        sasuke = min_tab(tabtab->tab[i],tabtab->nbcol);
        if (sasuke != -1) tableau_participant[sasuke]++;
    }
    melenchon = max_tab(tableau_participant,tabtab->nbcol, &max, -1);
    if(max > tabtab->nblignes/2) return melenchon;
    zemmour = max_tab(tableau_participant,tabtab->nbcol, &max, melenchon);
    free(tableau_participant);
    int position=0;
    for (int i=0; i<tabtab->nblignes; i++) {
        if (tabtab->tab[i][melenchon] < tabtab->tab[i][zemmour])position++;
        if (tabtab->tab[i][melenchon] > tabtab->tab[i][zemmour])position--;
    }
    if (position > 0) return melenchon;
    if (position < 0) return zemmour;
    return (melenchon-zemmour)>0 ? melenchon : zemmour; // l'index le plus grand gagne
}
