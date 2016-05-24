#include"CentreDechets.h"

void* routineCentreDechets (void* arg){

    CentreDechets* centre = (CentreDechets *) arg;
    int i;
    int continueChargement;
    CamionCaract** tempC = malloc(sizeof(CamionCaract*));
    Poubelle** tempP = malloc(sizeof(Poubelle*));

    while(1){

        if(premierCamionLibre(centre->camions,centre->nbCamion,tempC) && (!isEmpty(&(centre->listPoubelle)))){
            i = 0;
            if((*tempC) != NULL){
                if(!isEmpty(&(centre->listPoubelle))){
                    continueChargement = 1;
                }
                else{
                    continueChargement = 0;
                }
                pthread_mutex_lock(&((*tempC)->mutex));
                while((i < (*tempC)->nbPoubelleMax) && continueChargement){
                    useFirst(&(centre->listPoubelle),tempP);
                    printf("poubelle a vider : %d\n",(*tempP)->id);

                    add(&((*tempC)->cible),*tempP);

                    if(!isEmpty(&(centre->listPoubelle))){
                        continueChargement = 1;
                    }
                    else{
                        continueChargement = 0;
                    }
                    ++i;
                }
                (*tempC)->dispo = 0;
                pthread_mutex_unlock(&((*tempC)->mutex));
                pthread_cond_signal(&((*tempC)->cond));
            }
            else{
                printf("erreur!!!!!!!!!!\n");
            }
        }
    }
}

void InitCentreDechets(CentreDechets* centre,CamionCaract* camions,int nbCamion){

    centre->camions = camions;
    centre->nbCamion = nbCamion;

    InitLinkedListPoubelle(&(centre->listPoubelle));


    centre->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    centre->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    pthread_create(&centre->pthread_id,NULL,routineCentreDechets,(void*)centre);
}

void* routinePoubelle(void* arg){
    Poubelle* p = (Poubelle*) arg;
    CentreDechets* centreDechets = (CentreDechets*) p->centreDechets;
    while(1){

        pthread_mutex_lock(&(p->mutex));
        pthread_cond_wait(&(p->cond),&(p->mutex));
        if(p->nbDechets >= ((60./100.) * p->contenanceMax)){
            if(!p->traitement){
                printf("appelle centre pour la poubelle %d\n",p->id);
                p->traitement = 1;
                add(&(centreDechets->listPoubelle),p);
            }
        }

        pthread_mutex_unlock(&(p->mutex));
    }
}

void InitPoubelle(Poubelle* p, float contenanceMax,void* centreDechets,int id){

    p->nbDechets = 0.0;
    p->nbDechetsSauvages = 0.0;
    p->id = id;
    p->contenanceMax = contenanceMax;
    p->traitement = 0;
    p->centreDechets = centreDechets;

    p->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    p->cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    pthread_create(&(p->pthread_id),NULL,routinePoubelle,(void*)p);

}
