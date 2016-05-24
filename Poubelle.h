#ifndef _POUBELLE_H_
#define _POUBELLE_H_

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

#define MAX_CONTENANCE_BORNE_CLE 30

typedef struct {
    pthread_t pthread_id;

    int id;
    int cle;

    int traitement;

    float nbDechets;
    float nbDechetsSauvages;
    float contenanceMax;

    void* centreDechets;

    pthread_mutex_t mutex;
    pthread_cond_t cond;

}Poubelle;

/*
 * Poubelle
 * pthread_id est l'id du thread de poubelle
 * id est le numero de poubelle pour la reconnaitre
 * cle est uttilise comme un booleen pour savoir si la poubelle a besoin d'une clé
 * traitement vaut 0 s'il n'a pas contacté le centre pour se faire vider 1 sinon
 * nbDechets est le nombre de dechets que contient une poubelle
 * nbDechetsSauvages est le nombre de déchets sauvage au pied de la poubelle
 * contenanceMaxest la contenance max de la poubelle
 * centreDechets est le centre déchet qu'elle doit appeller pour vider la poubelle
 * mutex est le mutex pour la poubelle
 * cond est la condition qui permet de mettre la poubelle en attente
 */


void vider(Poubelle* p,int camionId);
/*
 *	cette fonction est utilisé par le camion lorsqu'il vide la poubelle
 *	elle réinitialise les déchets et déchets sauvage à 0 et passe l'entier
 *	traitement à 0
 */

int jeter(Poubelle* p,Poubelle* pCommune,float nbDechets,int cle);
/*
 * retourne 1 s'il est possible de jeter tous les déchets dans la poubelle
 * p est la poubelle dans laquelle on souhaite jeter les dechets
 * nbDechets est le quantité de déchets que l'on souhaite jeter
 */

void depotSauvage(Poubelle* p,float nbDechets);

/*
 * jette nbDechets dans les dépots sauvage de la poubelle p
 */
#endif
