#include "Camion.h"

void InitCamion(CamionCaract* c,int nbPoubelleMax,int id){

    c->dispo = 1;
    c->id = id;

    c->nbPoubelleMax = nbPoubelleMax;

    InitLinkedListPoubelle(&(c->cible));

    c->mutex =(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    c->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    pthread_create(&c->pthread_id,NULL,routineCamion,(void*)c);
}

void* routineCamion(void* arg){

    CamionCaract* caract = (CamionCaract*) arg;
    Poubelle *tempP;
    while(1){

        pthread_mutex_lock(&(caract->mutex));
        pthread_cond_wait(&(caract->cond),&(caract->mutex));

        while(!isEmpty(&(caract->cible))){
            pthread_mutex_unlock(&(caract->mutex));
            useFirst(&(caract->cible),&tempP);
            vider(tempP,caract->id);
            pthread_mutex_lock(&(caract->mutex));
        }
        pthread_mutex_unlock(&(caract->mutex));
        sleep(1);
        pthread_mutex_lock(&(caract->mutex));

        caract->dispo = 1;

        pthread_mutex_unlock(&(caract->mutex));

    }

    return NULL;
}


int premierCamionLibre(CamionCaract* camionListe, int nbCamion, CamionCaract** camionTrouve){

    int i = 0,trouve = 0;

    while(i < nbCamion && !trouve){

        pthread_mutex_lock(&(camionListe[i].mutex));

        if(camionListe[i].dispo){
            trouve = 1;
            *camionTrouve = &camionListe[i];
        }
        pthread_mutex_unlock(&(camionListe[i].mutex));
        i++;
    }
    if(trouve){
        return 1;
    }
    else{
        (*camionTrouve) = NULL;
        return 0;
    }
}
