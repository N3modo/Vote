/// \file Main.c
/// \author Anthony PAILLA
/// \date november 2021

#include "test_uninominal.h"
#include "main.h"


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
        dup2(STDERR_FILENO,loglog);
    }
    if (i && d){
        printf("option -i et -d mutuellement exclusives");
        exit(EXIT_FAILURE);
    }
    if (!(i||d)){
        printf("option -i ou -d requise");
        exit(EXIT_FAILURE);
    }
    if (mode == 0){
        printf("option -m requise");
        exit(EXIT_FAILURE);
    }
    int score_gagnant;
    MonTableau tabtab = read_csv(filename,0,4); // pb à corrigé
    switch (mode) {
        case 1:
            id_gagnant=uninominale1(&tabtab,&score_gagnant);
            printf("mode de scrutin : uninominal a 1 tour, %d candidats, %d votants, vainqueur = %s, score = %.2f %%",tabtab.nbcol,tabtab.nblignes,tabtab.tabName[id_gagnant],(float)score_gagnant*100/(float)tabtab.nblignes);
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
