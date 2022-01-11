/// \file utilitaires.c
/// \author Anthony PAILLA
/// \date decembre 2021

#include "utilitaires.h"

#include <errno.h>

int *createDynamiqueTab1D(int ligne){
/// \fn fonction createDynamiqueTab1D
/// \param[in] nb de ligne
/// \return tableau 1D
/// \brief creer un tableau d'entier dynamique à une dimension
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

void destroyDynamiqueTab1D(int * tab){
/// \fn fonction destroyDynamiqueTab1D
/// \param[in] tableau 1D
/// \brief free tableau 1D
    free(tab);
}

int **createDynamiqueTab2D(int ligne, int nbcolonne){
/// \fn fonction createDynamiqueTab2D
/// \param[in] nb de ligne et nb de colonne
/// \return tableau 2D
/// \brief creer un tableau d'entier dynamique à deux dimensions
    int** tab2d = NULL;
    if (ligne > 0){
        tab2d= (int **) malloc(ligne*sizeof(int*));
        if(tab2d==NULL){exit(EXIT_FAILURE);}
        for(int i=0;i<ligne;i++){
            tab2d[i]=malloc(nbcolonne*sizeof(int));
            if(tab2d[i]==NULL){exit(EXIT_FAILURE);}
        }
    }
    return tab2d;
}

void destroyDynamiqueTab2D(int ** tab, int ligne){
/// \fn fonction destroyDynamiqueTab2D
/// \param[in] tableau 2D et nb de ligne
/// \brief free tableau 2D
    for(int i=0;i<ligne;i++){
        free(tab[i]);
    }
    free(tab);
}

int nombreCandidats(char * ligne,int offsetCol){
    char* votecourant;
    int taille = 0;
    votecourant=strtok(ligne,",");
    while(votecourant != NULL){
        taille++;
        votecourant=strtok(NULL,",");
    }
    return taille-offsetCol;
}

int nombreLignes(FILE * votes,int offsetLigne){
    size_t n;
    char * temp = NULL;
    int taille = 0;
    while(getline(&temp,&n,votes) != -1){
        taille++;
    }
    return taille-offsetLigne;
}

void ModifierTailleTableau(MonTableau *tab, int nbColonne, int nbLigne){
/// \fn fonction ModifierTailleTableau
/// \param[in] structure MonTableau et un entier ( axe y ou x)
/// \brief modifier taille d'un struct tableau
    if(nbLigne != tab->nblignes){
        if(tab->nblignes == 0){
            tab->tab=(int**)malloc(nbLigne*sizeof(int*));
        }else{
            tab->tab=(int**)realloc(tab->tab,nbLigne*sizeof(int*));
        }
        for(int i = tab->nblignes; i< nbLigne;i++){
            if (tab->nbcol != 0) tab->tab[i] = (int*) malloc((tab->nbcol)*sizeof(int));
        }
        tab->nblignes=nbLigne;
    }
    if(nbColonne != tab->nbcol){
        for (int i=0;i<tab->nblignes;i++){
            if (tab->nbcol == 0) {
                tab->tab[i]=(int*)malloc(nbColonne*sizeof(int));
            }else{
                tab->tab[i]=(int*)realloc(tab->tab[i],(nbColonne)*sizeof(int));
            }
        }
        if(tab->nbcol==0){
          tab->tabName=(char**)malloc(nbColonne*sizeof(char*));
        }else{
          tab->tabName=(char**)realloc(tab->tabName,(nbColonne)*sizeof(char*));
        }
        tab->nbcol = nbColonne;
    }
}

void InitTableau(MonTableau *tab){
/// \fn fonction InitTableau
/// \param[in] structure MonTableau
/// \brief initialisation struct tab
    tab->nblignes = 0;
    tab->nbcol= 0;
}

void freeThemAll(MonTableau *tabtab){
/// \fn fonction freeThemAll
/// \param[in] structure MonTableau
/// \brief free structure
    for(int i=0; i<tabtab->nblignes;i++){
        free(tabtab->tab[i]);
    }
    free(tabtab->tab);
    free(tabtab->tabName);
}

void afficherTab2D(int ** tab,int lig, int col, FILE * log){
/// \fn fonction afficherTab2D
/// \param[in] structure MonTableau
/// \brief affichage d'un tableau 2D
    fprintf(log,"\n");
    for(int l=0; l<lig; l++){
        for(int c=0; c<col; c++){
            fprintf(log,"%d ",tab[l][c]);
        }
        fprintf(log,"\n");
    }
    fprintf(log,"\n");
}

void afficherTab1D(int * tab,int taille,FILE * log){
    /// \fn fonction afficherTab1D
    /// \param[in] structure MonTableau
    /// \brief affichage d'un tableau 1D
    fprintf(log,"\n");
    for (int i =0; i<taille;i++){
        fprintf(log,"%d ",tab[i]);
    }
    fprintf(log,"\n");
}

int min_tab(int *tab, int taille, int * min, int excl){
/// \fn fonction min_tab
/// \param[in] tableau 1D, un entier (taille), un pointer d'entier (min) et un entier (excl)
/// \return un entier (position)
/// \brief minimum d'un tableau
    int position=0;
    if(position==excl) position++;
    *min=tab[position];
    for (int i=0; i<taille;i++){
        if ((tab[i]<=*min) && (i != excl)){
            *min=tab[i];
            position = i;
        }
    }
    return position;
}

int max_tab(int *tab, int taille, int * max, int excl){
/// \fn fonction max_tab
/// \param[in] tableau 1D, un entier (taille), un pointer d'entier (min) et un entier (excl)
/// \return un entier (position)
/// \brief maximum d'un tableau
    int position=0;
    if(position==excl) position++;
    *max=tab[position];
    for (int i=0; i<taille;i++){
        if ((tab[i]>=*max) && (i != excl)){
            *max=tab[i];
            position = i;
        }
    }
    return position;
}





MonTableau read_csv(char *filename, int offsetLigne, int offsetCol){
    /// \fn fonction lecture fichier CSV
    /// \param[in] un fichier, un offset pour les lignes et un offset pour les colonnes
    /// \brief traite un fichier csv et le renvoie en struct MonTableau
    char *ligne= NULL;
    char *votecourant;
    size_t n = 0;
    fprintf(stderr,"Ouverture de : %s\n",filename);

    FILE* fd = fopen(filename,"r");
    if (fd == NULL) perror("Echec de l'ouverture du fichier");
    int nbVotants = nombreLignes(fd,offsetLigne+1);
    fclose(fd);
    fd = fopen(filename,"r");
    if (fd == NULL) perror("Echec de l'ouverture du fichier");
    for (int i=offsetLigne; i>0; i--) getline(&ligne,&n,fd); //offset des lignes
    getline(&ligne,&n,fd);
    int nbcandidats = nombreCandidats(ligne,offsetCol); //le vrai truc
    fclose(fd);
    MonTableau tablo;
    InitTableau(&tablo);
    ModifierTailleTableau(&tablo,nbcandidats,nbVotants);
    fd = fopen(filename,"r");
    if (fd == NULL) perror("Echec de l'ouverture du fichier");
    for (int i=offsetLigne; i>0; i--) getline(&ligne,&n,fd); //offset des lignes
    getline(&ligne,&n,fd);
    ligne[strlen(ligne)-1] ='\0'; //magie noire pour eviter le \n
    votecourant=strtok(ligne,",");
    for (int i=offsetCol; i>0; i--) votecourant=strtok(NULL,",");
    int candidat_actuel = 0;
    while(votecourant != NULL){
        tablo.tabName[candidat_actuel] = (char*)malloc(strlen(votecourant)* sizeof(char));
        strcpy(tablo.tabName[candidat_actuel],votecourant);
        votecourant=strtok(NULL,",");
        candidat_actuel++;
    }

    for(int lig = 0; (getline(&ligne,&n,fd) != -1) && (lig < tablo.nblignes); lig++){
        votecourant=strtok(ligne,",");
        for (int i=offsetCol; i>0; i--) votecourant=strtok(NULL,","); //on skip tout$
        for( int col = 0; col < tablo.nbcol; col++){
            sscanf(votecourant,"%d",&(tablo.tab[lig][col]));
            votecourant=strtok(NULL,",");
        }
    }
    free(ligne);
    fclose(fd);
    return tablo;
}
