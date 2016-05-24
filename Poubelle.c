#include "Poubelle.h"


void vider(Poubelle *p,int camionId){

    pthread_mutex_lock(&(p->mutex));

    printf("\t\t\tpoubelle %d vider de %f dechets normaux et de %f dechetsSauvages, par le camion %d\n",p->id,p->nbDechets,p->nbDechetsSauvages,camionId);

    p->nbDechets = 0;
    p->nbDechetsSauvages = 0;

    p->traitement = 0;

    pthread_mutex_unlock(&(p->mutex));
}

int jeter(Poubelle* p,Poubelle* pCommune, float nbDechets,int cle){

    if(p != NULL){

        pthread_mutex_lock(&(p->mutex));
        if(p->nbDechets + nbDechets <= p->contenanceMax){
            printf("on jette %f dechet dans la poubelle %d \n",nbDechets,p->id);

            p->nbDechets += nbDechets;

            printf("il y a maintenant %f dechets dans la poubelle %d \n",p->nbDechets,p->id);

            pthread_cond_signal(&(p->cond));

            pthread_mutex_unlock(&(p->mutex));

            return 1;
        }
        pthread_mutex_unlock(&(p->mutex));
    }
    if(pCommune!=NULL){
        pthread_mutex_lock(&(pCommune->mutex));

        if((cle) && (pCommune->nbDechets + nbDechets <= pCommune->contenanceMax)){
            printf("on jette %f dechet dans la poubelle commune %d \n",nbDechets,pCommune->id);

            pCommune->nbDechets += nbDechets;

            printf("il y a maintenant %f dechets dans la poubelle commune %d \n",pCommune->nbDechets,pCommune->id);

            pthread_cond_signal(&(pCommune->cond));

            pthread_mutex_unlock(&(pCommune->mutex));

            return 1;
        }
        pthread_mutex_unlock(&(pCommune->mutex));
    }

    printf("pas assez de place pour jeter la poubelle\n");
    if(p != NULL){
        depotSauvage(p,nbDechets);
        return 0;
    }
    else if(pCommune != NULL){
        depotSauvage(pCommune,nbDechets);
        return 0;
    }
    return 0;
}

void depotSauvage(Poubelle* p, float nbDechets){
    pthread_mutex_lock(&(p->mutex));

    printf("on jette %f dechets SAUVAGE\n",nbDechets);
    p->nbDechetsSauvages += nbDechets;
    printf("il y a maintenant %f dechets SAUVAGE dans la poubelle %d\n",p->nbDechetsSauvages,p->id);
    pthread_mutex_unlock(&(p->mutex));
}



