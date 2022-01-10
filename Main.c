/// \file Main.c
/// \author Anthony PAILLA
/// \date november 2021

#include "Uninominal.h"
#include "Condorcet.h"
#include "Main.h"


int main(int argc, char *argv[]) {
/// \fn Fonction main
    if (argc==1) printf("usage: *.exe (-i | -d) filename -m (uni1,uni2,all | cm,cs,all) [-o logfile]\n");
    int opt,mode=0,loglog;
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
            default: printf("usage: %s (-i | -d) filename -m (uni1,uni2,cm,cs,all) [-o logfile]",argv[0]); //erreur si non respect de l'usage
                exit(EXIT_FAILURE);
        }
    }
    if(o){
        loglog = (int) fopen(logfile,"a");
        dup2(STDERR_FILENO,loglog);
    }
    if (i && d){ //erreur si i et d
        printf("option -i et -d mutuellement exclusives");
        exit(EXIT_FAILURE);
    }
    if (!(i||d)){ //erreur si pas de i ni de d
        printf("option -i ou -d requise");
        exit(EXIT_FAILURE);
    }
    if (mode == 0){ //erreur si pas de mode
        printf("option -m requise");
        exit(EXIT_FAILURE);
    }
    if (d==1){ //vote par matrice de duel
        MonTableau tabtab = read_csv(filename,0,4);
        switch (mode) {
            case 3: //condorcet minimax
                Minimax(&tabtab);
                break;
            case 4: //condorcet schulze
                Schulze(&tabtab);
                break;
            case 5: //all
                Minimax(&tabtab);
                Schulze(&tabtab);
                break;
            default: printf("usage: %s (-d) filename -m (cm,cs,all) [-o logfile]",argv[0]); //erreur si non respect de l'usage
                exit(EXIT_FAILURE);
        }
        freeThemAll(&tabtab);
        fclose((FILE *)loglog);
        return 0;
    }
    if (i==1){ //vote par classement
        MonTableau tabtab = read_csv(filename,0,4);
        switch (mode) {
            case 1: //uninominal 1
                uninominale1(&tabtab);
                break;
            case 2: //uninominal 2
                uninominale2(&tabtab);
                break;
            case 5: //all
                uninominale1(&tabtab);
                uninominale2(&tabtab);
                break;
            default: printf("usage: %s (-i) filename -m (uni1,uni2,all) [-o logfile]",argv[0]); //erreur si non respect de l'usage
                exit(EXIT_FAILURE);
        }
        freeThemAll(&tabtab);
        fclose((FILE *)loglog);
        return 0;
    }
}