#include "LinkedListPoubelle.h"


void InitLinkedListPoubelle(LinkedListPoubelle* l){
    l->first = NULL;
    l->last = NULL;
    l->mutex =(pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
}
void add(LinkedListPoubelle* l, Poubelle * p){
    maillon *tempM;
    pthread_mutex_lock(&(l->mutex));
    if(p != NULL){
        tempM = malloc(sizeof(maillon));
        tempM->p = p;
        tempM->next = NULL;
        if(l->first == NULL){
            l->first = tempM;
            l->last = tempM;
        }
        else{
            l->last->next = tempM;
            l->last = tempM;
        }
    }
    pthread_mutex_unlock(&(l->mutex));
}

void useFirst(LinkedListPoubelle* l, Poubelle **p){
    maillon *tempM;
    pthread_mutex_lock(&(l->mutex));
    if(l->first != NULL){
        *p = (l->first->p);
        tempM = l->first;
        l->first = tempM->next;
        if(tempM->next == NULL){
            l->last = NULL;
        }
        if(tempM != NULL){
            free(tempM);
        }
        else{
            printf("erreur!!!!!!!!!");
        }
    }
    pthread_mutex_unlock(&(l->mutex));
}

int isEmpty(LinkedListPoubelle* l){
    int empty;
    pthread_mutex_lock(&(l->mutex));
    if(l->first == NULL){
        empty = 1;
    }
    else{
        empty = 0;
    }
    pthread_mutex_unlock(&(l->mutex));

    return empty;
}


