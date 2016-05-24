#ifndef _USAGER_H_
#define _USAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "Poubelle.h"

typedef struct {
    pthread_t id;
    int vitesse_dechet;
    int cle;
    int bac;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    Poubelle* poubelle_perso;
    Poubelle* poubelle_commune;
}Foyer;
/*
 * Foyer
 * pthread_id est l'id du thread du centre
 * vitesse_dechet décrit la vitesse du foyer à jeter des déchets
 * cle vaut 1 si le foyer à une clé pour la poubelle collective 0 sinon
 * bac vaut 1 si le foyer à un bac personnel 0 sinon
 * mutex est le mutex pour la poubelle
 * cond est la condition qui permet de mettre la poubelle en attente
 * poubelle_perso est le bac du foyer
 * poubelle_commune est la poubelle à clé dont le foyer à accès
 */


void InitUsager(int nombreHab,Foyer* foyer,Poubelle* poubelle_perso, Poubelle* poubelle_commune,int cle, int bac);
/*
 *	cette fonction initialise un thread usager
 */
void* routineUsager(void* arg);
/*
 * 	cette fonction est la fonction qu'exécute un thread Usager
 */
#endif
