#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "Poubelle.h"
#include "Usager.h"
#include "Camion.h"
#include "CentreDechets.h"
int main(int argc,char ** argv){

    int nbCamion;
    int nbFoyer;
    int nbPoubelleParCamion;
    int nbPoubelleCommune;
    int nbFoyerSansBac;
    int i;

    CentreDechets centreDechets;
    Foyer* foyer;
    CamionCaract* camions;
    Poubelle* pCommune;
    Poubelle* bac;


    printf("entrez le nombre de camion\n");
    scanf("%d",&nbCamion);
    printf("entrez le nombre de poubelle que peut contenir un camion\n");
    scanf("%d",&nbPoubelleParCamion);
    printf("entrez le nombre d'usager\n");
    scanf("%d",&nbFoyer);
    printf("entrez le nombre de poubelle commune\n");
    scanf("%d",&nbPoubelleCommune);
    printf("entrez le nombre de foyer sans bac\n");
    scanf("%d",&nbFoyerSansBac);

    srand(time(NULL));

    camions = malloc(nbCamion*sizeof(CamionCaract));
    foyer = malloc(nbFoyer * sizeof(Foyer));
    pCommune = malloc(nbPoubelleCommune* sizeof(Poubelle));
    bac = malloc((nbFoyer - nbFoyerSansBac)*sizeof(Poubelle));

    for(i = 0; i < nbCamion; ++i){
        InitCamion(camions + i,nbPoubelleParCamion,i);
    }

    InitCentreDechets(&centreDechets,camions,nbCamion);

    for(i = 0; i < (nbFoyer - nbFoyerSansBac); ++i){
        InitPoubelle((bac + i),300,(void*) (&centreDechets),i);
    }

    for(i = 0; i < nbPoubelleCommune; ++i){
        InitPoubelle((pCommune + i),300.0,(void*)(&centreDechets),i);
    }


    for(i = 0; i < (nbFoyer - nbFoyerSansBac); ++i){
        InitUsager(rand()%6,foyer,(bac + i),(pCommune +(i%nbPoubelleCommune)),rand()%2,1);
    }
    for(i = (nbFoyer - nbFoyerSansBac); i < nbFoyer; ++i){
        InitUsager(rand()%6,foyer,NULL,(pCommune +(i%nbPoubelleCommune)),1,0);
    }

    for(i = 0; i < nbCamion; ++i){
        pthread_join(camions[i].pthread_id,NULL);
    }

    for(i = 0; i < nbFoyer; ++i){
        pthread_join(foyer[i].id,NULL);
    }

    pthread_join(centreDechets.pthread_id,NULL);

    return 0;
}


