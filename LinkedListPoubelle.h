#ifndef _LINKED_LIST_POUBELLE_H_
#define _LINKED_LIST_POUBELLE_H_

#include <stdio.h>
#include <stdlib.h>

#include "Poubelle.h"

typedef struct maillon{

    Poubelle* p;

    struct maillon* next;

}maillon;

typedef struct {

    maillon* first;
    maillon* last;

    pthread_mutex_t mutex;

}LinkedListPoubelle;

void InitLinkedListPoubelle(LinkedListPoubelle* l);
/*
 * fonction qui initialise correctement une liste chainee de poubelle
 */

void add(LinkedListPoubelle* l,Poubelle *p);
/*
 * fonction qui ajoute un nouveau maillon contenant l'adresse de la poubelle a ajouter
 * le maillon est ajouter en fin de liste
 */

void useFirst(LinkedListPoubelle* l,Poubelle **p);
/*
 * fonction qui stocke l'adresse de la poubelle du premier maillon de la chaine dans p
 * La fonction suprime aussi le premier maillon une fois l'adresse de poubelle recuere
 */

int isEmpty(LinkedListPoubelle* l);
/*
 * fonction qui renvoie 1 si la liste est vide, 0 sinon
 */


#endif
