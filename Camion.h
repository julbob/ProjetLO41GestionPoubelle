#ifndef _CAMION_H_
#define _CAMION_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "LinkedListPoubelle.h"

typedef struct{
    pthread_t pthread_id;
    int id;
    int dispo;
    LinkedListPoubelle cible;
    int nbPoubelleMax;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}CamionCaract;
/*
 * CamionCaract contient toutes les caracteristiques d'un camion plus l'id de son thread et un mutex pour sécuriser les accès concurrents
 * pthread_id est l'identifiant pour le thread du camion
 * dispo est utilisé comme un booléen : 1 le camion est disponible, 0 le camion est en cours d'utilisation
 * cible est une liste de toutes les poubelles que doit vider un camion
 * nbPoubelleMax est le nombre max de poubelle qu'un camion peut vider en un voyage
 * mutex est un mutex
 * cond est une pthread cond qui permet de savoir si le camion peut partir ou si il continue a rien faire
 */

int appelleCamion(CamionCaract centreDechet[] ,int nbCamion,Poubelle* cible);
/*
 * fonction qui renvoie 1 si elle a reussi à trouver et envoyer un camion vider la poubelle cible
 * centreDechet est un tableau de camionCaract qui contient tous les camions de la ville
 * nbCamion est le nombre de camion dont dispose la ville
 * cible est la poubelle à vider
 */

void InitCamion(CamionCaract* c,int nbPoubelleMax,int id);
/*
 * initialise le camion
 */

void* routineCamion(void* arg);
/*
 * cette fonction est la fonction que les thread camion exécute
 */

int premierCamionLibre(CamionCaract* camionListe, int nbCamion, CamionCaract** camionTrouve);

/*
 * fonction qui renvoie 1 si elle a reussi à trouver un camion libre et le récupère dans camionTrouve
 * camionListe est un tableau de camionCaract qui contient tous les camions du centre de déchets
 * nbCamion est le nombre de camion dont dispose le centre de déchets
 */


#endif

