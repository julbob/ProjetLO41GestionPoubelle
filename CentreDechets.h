#ifndef _CENTRE_DECHETS_H_
#define _CENTRE_DECHETS_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "Poubelle.h"
#include "Camion.h"
#include "LinkedListPoubelle.h"

typedef struct {

    pthread_t pthread_id;

    pthread_cond_t cond;
    pthread_mutex_t mutex;

    CamionCaract* camions;
    int nbCamion;

    LinkedListPoubelle listPoubelle;

}CentreDechets;
/*
 * CentreDechets
 * pthread_id est l'id du thread du centre
 * camions est la liste de camions dont dispose le centre
 * nbCamion est le nombre de camions dont dispose le centre
 * mutex est le mutex pour la poubelle
 * cond est la condition qui permet de mettre la poubelle en attente
 */

void* routineCentreDechets (void* arg);
/*
 *	cette fonction est la fonction qu'exécute le thread du centre
 */

void InitCentreDechets(CentreDechets* centre,CamionCaract* camions,int nbCamion);
/*
 *	cette fonction initialise le centre de déchets
 */
void* routinePoubelle(void* arg);
/*
 *	cette fonction est la fonction qu'exécute les threads poubelle
 */

void InitPoubelle(Poubelle* p, float contenanceMax,void* centreDechets,int id);
/*
 *	cette fonction initialise une poubelle
 */

#endif
