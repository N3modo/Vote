/// \file debut.h
/// \author Anthony PAILLA
/// \date november 2021
#include "test_uninominal.h"


int *createDynamiqueTab1D(int ligne){ //creer un tableau d'entier dynamique à une dimension
  int* tab1d = NULL;
  if (ligne > 0){
    tab1d = (int *) malloc(ligne * sizeof(int));
    if(tab1d==NULL){
      exit(EXIT_FAILURE);
    }
    for (int i=0; i<ligne; i++){
        tab1d[i]=0;
    }
  }
  return tab1d;
}

int **createDynamiqueTab2D(int ligne, int nbcolonne){ //creer un tableau d'entier dynamique à deux dimensions
  int** tab2d = NULL;
  if (ligne > 0){
    tab2d= (int **) malloc(ligne*sizeof(int));
    if(tab2d==NULL){exit(EXIT_FAILURE);}
    for(int i=0;i<ligne;i++){
      tab2d[i]=malloc(nbcolonne*sizeof(int));
      if(tab2d[i]==NULL){exit(EXIT_FAILURE);}
    }
  }
  return tab2d;
}

char **createDynamiqueStringTab2D(int ligne, int nbcolonne){ //creer un tableau de chaine de caracteres dynamique à deux dimensions
  char** tab2dstring = NULL;
  if (ligne>0){
    tab2dstring = malloc(ligne*sizeof(char));
    if (tab2dstring == NULL){exit(EXIT_FAILURE);}
    for(int i=0;i<ligne;i++){
      tab2dstring[i]=malloc(nbcolonne*sizeof(char));
      if (tab2dstring[i] == NULL){exit(EXIT_FAILURE);}
    }
  }
  return tab2dstring;
}

void ModifierTailleTableau(MonTableau *tab, int axe){
    switch(axe){
        case 'y': //augmente le nombre de ligne
            tab->nblignes++;
            if (tab->nblignes == 1) {
                tab->tab=(int**)malloc(sizeof(int*));
            }else{
                tab->tab=(int**)realloc(tab->tab,(tab->nblignes)*sizeof(int*));
            }
            if (tab->nbcol != 0) tab->tab[tab->nblignes-1] = (int*) malloc((tab->nbcol)*sizeof(int));
            break;
        case 'x': //augmente le nombre de colonne
            tab->nbcol++;
            for (int i=0;i<tab->nblignes;i++){
                if (tab->nbcol == 1) {
                    tab->tab[i]=(int*)malloc(sizeof(int));
                }else{
                    tab->tab[i]=(int*)realloc(tab->tab[i],(tab->nbcol)*sizeof(int));
                }
            }
            if (tab->nbcol == 1) { //fait en sorte que le nombre de candidat soit egal au nombre de colonne
                tab->tabName=(char**)malloc(sizeof(char*));
            }else{
                tab->tabName=(char**)realloc(tab->tabName,(tab->nbcol)*sizeof(char*));
            }
            break;
        default:
            return;
    }
}

void InitTableau(MonTableau *tab){
    tab->nblignes = 0;
    tab->nbcol= 0;
}

void freeThemAll(MonTableau *tabtab){
    for(int i=0; i<tabtab->nblignes;i++){
        free(tabtab->tab[i]);
    }
    free(tabtab->tab);
    free(tabtab->tabName);
}


void afficherTab(MonTableau *tab){
    for(int l=0; l<tab->nblignes; l++){
        for(int c=0; c<tab->nbcol; c++){
            printf("%d ",tab->tab[l][c]);
        }
        printf("\n");
    }
}
MonTableau read_csv(char *filename, int offsetLigne, int offsetCol){
    FILE* fd = fopen(filename,"r");
    char *ligne=NULL;
    char *votecourant;
    size_t n;
    MonTableau tablo;
    InitTableau(&tablo);
    for (int i=offsetLigne; i>0; i--) getline(&ligne,&n,fd);
    int lig=0;
    getline(&ligne,&n,fd);
    ligne[strlen(ligne)-1] ='\0';
    votecourant=strtok(ligne,","); // <===== ici le ptn de probleme
    for (int i=offsetCol; i>0; i--) votecourant=strtok(NULL,",");
    while(votecourant != NULL){
        ModifierTailleTableau(&tablo,'x');
        tablo.tabName[tablo.nbcol-1]= (char*)malloc(strlen(&(votecourant[26]))* sizeof(char));
        strcpy(tablo.tabName[tablo.nbcol-1],&(votecourant[26]));
        votecourant=strtok(NULL,",");
    }
    while (getline(&ligne,&n,fd) != -1){
        ModifierTailleTableau(&tablo,'y');
        int col=0;
        votecourant=strtok(ligne,",");
        for (int i=offsetCol; i>0; i--) votecourant=strtok(NULL,",");
        while (votecourant != NULL){
            if (col >= tablo.nbcol) ModifierTailleTableau(&tablo,'x');
            sscanf(votecourant,"%d",&(tablo.tab[lig][col]));
            votecourant=strtok(NULL,",");
            col++;
        }
        lig++;
    }
    free(ligne);
    fclose(fd);
  return tablo;
}
/*
void tab1d_in_struct(){}
void tab2d_in_struct(){}
void tab2dstring_in_struct(){}
*/
int main(int argc, char *argv[]) {
    int opt,mode=0,id_gagnant=-1,loglog;
    bool i=0,d=0,o=0;
    char *filename, *logfile;
    while ((opt = getopt(argc, argv, "idom")) != -1) {
        switch(opt) {
            case 'i':
                filename = argv[optind];
                i=1;
                break;
            case 'd':
                filename = argv[optind];
                d=1;
                break;
            case 'o':
                logfile = argv[optind];
                o=1;
                break;
            case 'm':
                if(!strcmp(argv[optind], "uni1")){
                    mode=1;
                }
                if(!strcmp(argv[optind], "uni2")){
                    mode=2;
                }
                if(!strcmp(argv[optind], "cm")){
                    mode=3;
                }
                if(!strcmp(argv[optind], "cs")){
                    mode=4;
                }
                if(!strcmp(argv[optind], "all")){
                    mode=5;
                }
                break;
            default: printf("usage: %s (-i | -d) filename -m (uni1,uni2,cm,cs,all) [-o logfile]",argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    if(o){
        loglog = (int) fopen(logfile,"a");
        dup2(STDOUT_FILENO,loglog);
    }
    if (i && d){
        printf("option -i et -d mutuellement exclusives");
        exit(EXIT_FAILURE);
    }
    if (mode == 0){
        printf("option -m requise");
        exit(EXIT_FAILURE);
    }
    MonTableau tabtab = read_csv(filename,0,4); // pb à corrigé
    switch (mode) {
        case 1:
            id_gagnant=uninominale1(&tabtab);
            printf("mode de scrutin : uninominal à 1 tour, %d candidats, %d votants, vainqueur = %s, score = à completer",tabtab.nbcol,tabtab.nblignes,tabtab.tabName[id_gagnant]);
            break;
        case 2:
            id_gagnant=uninominale2(&tabtab);
            printf("mode de scrutin :%s", tabtab.tabName[id_gagnant]);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }
    freeThemAll(&tabtab);
    fclose((FILE *)loglog);
  return 0;
}