#include "Usager.h"

void InitUsager(int nombreHab,Foyer* foyer, Poubelle* poubelle_perso, Poubelle* poubelle_commune,int cle, int bac){
    if(poubelle_perso != NULL){
        pthread_mutex_lock(&(poubelle_perso->mutex));
        if(nombreHab==1){
            poubelle_perso->contenanceMax=80;
        }
        else if(nombreHab==2){
            poubelle_perso->contenanceMax=120;
        }
        else if(nombreHab==3||nombreHab==4){
            poubelle_perso->contenanceMax=180;
        }
        else if(nombreHab>=5){
            poubelle_perso->contenanceMax=240;
        }
        pthread_mutex_unlock(&(poubelle_perso->mutex));
    }
    foyer->poubelle_perso = poubelle_perso;
    foyer->poubelle_commune = poubelle_commune;
    foyer->cle = cle;
    foyer->bac = bac;
    srand(time(NULL));
    foyer->vitesse_dechet = (rand()%10) * nombreHab;
    foyer->mutex =(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    foyer->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    pthread_create(&(foyer->id),NULL,routineUsager,(void*) foyer);
}

void* routineUsager(void* arg){
    Foyer* foyer = (Foyer*) arg;
    Poubelle* poubelle_perso = foyer->poubelle_perso;
    Poubelle* poubelle_commune = foyer->poubelle_commune;
    float dechets = 0.0;
    while(1){

        dechets = foyer->vitesse_dechet;
        jeter(poubelle_perso,poubelle_commune,dechets,foyer->cle);

        sleep(1);
    }


}
