//
// Created by florin on 3/22/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "lab04.h"

node_t * init_node(int *value) {
    node_t *new_node = malloc(sizeof(node_t));

    new_node->data = malloc(sizeof(int));
    *new_node->data = *value;

    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

list_t *init_list() {
    list_t *new_list = malloc(sizeof(list_t));

    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->len = 0;

    return new_list;
}

void free_node(node_t *nod)
{
    free(nod->data);
    free(nod);
}

void destroy_list(list_t *list) {
    node_t *aux;

    /* Se sterg toate nodurile din lista, incepand de la coada */
    while (list->len > 0) {
        aux = list->tail;                   // Se retine un pointer catre ultimul nod din lista
        list->tail = list->tail->prev;      // Se muta pointerul cozii cu un nod mai in spate
        free_node(aux);                // Se elibereaza memoria ocupata de nodul eliminat
        --list->len;                        // Se decrementeaza lungimea listei
    }

    /* Se elibereaza memoria ocupata de structura listei */
    free(list);
}

void print_list(list_t *list) {
    node_t *aux = list->head;

    printf("%-25s", "Lista construita (->):");

    if (aux == NULL) {
        // Lista vida
        printf("NULL\n");
        return;
    }

    while (aux != list->tail) {
        printf("%d -> ", *aux->data);
        aux = aux->next;
    }
    printf("%d\n", *aux->data);
}

void print_list_reversed(list_t *list) {
    
    printf("%-25s", "Lista inversata (->):");

    node_t *nod = list->tail;

    if(nod == NULL)
    {
        printf("Lista nula\n");
        return;
    }

    while (nod!=list->head)
    {
        printf("%d -> ", *nod->data);
        nod = nod->prev;        
    }
    printf("%d\n", *nod->data);
}

int insert_node(list_t *list, int value, int position) {

    node_t *nod = init_node(&value);

    if (position < 0 || position > list->len) return -1;

    if (list->len == 0)
    {
        list->head=nod;
        list->tail=nod;
        list->len++;

        return 0;
    }

    if (position == 0)
    {
        nod->next = list->head;
        list->head->prev = nod;
        list->head = nod;
        list->len++;

        return 0;
    }

    if (position == list->len)
    {
        nod->prev = list->tail;
        list->tail->next = nod;
        list->tail = nod;
        list->len++;
    
        return 0;
    }

    if (position <= list->len/2)
    {
        node_t *aux = list->head;
        int i=0;

        for (;i<position;i++)
        aux = aux->next;

        nod->next = aux;
        nod->prev = aux->prev;
        nod->prev->next = nod;
        aux->prev = nod;

        list->len++;

        return 0;
    }

    if (position > list->len/2)
    {
        node_t *aux = list->tail;
        int i = list->len-1;

        for (;i>position;i--)
        aux = aux->prev;

        nod->next = aux;
        nod->prev = aux->prev;
        nod->prev->next = nod;
        aux->prev = nod;
        
        list->len++;

        return 0;
    }

    return 0;
}

int remove_node(list_t *list, int position) {
    /* TODO 1.c.
     * Se vor trata urmatoarele cazuri:
     *  - Pozitia nu este in intervalul [0, len - 1] sau lista este vida (len == 0) => return -1
     *  - Stergerea se face de la inceputul listei
     *  - Stergerea se face de la sfarsitul listei
     *  - Stergerea se face dintr-o pozitie intermediara:
     *      - Pozitia este mai aproape de inceputul listei => parcurgerea se va face de la inceputul listei
     *      - Pozitia este mai aproape de sfarsitul listei => parcurgerea se va face de la sfarsitul listei
     */

    if (position < 0 || position > list->len-1 || list->len==0) 
        return -1;

    if (position == 0)
    {
        node_t *nod = list->head;
        
        list->head = nod->next;
        nod->next->prev = NULL;

        free_node(nod);
        list->len--;

        return 0;
    }

    if (position == list->len-1)
    {
        node_t *nod = list->tail;

        list->tail = nod->prev;
        nod->prev->next = NULL;

        free_node(nod);
        list->len--;

        return 0;
    }

    if (position <= (list->len-1)/2)
    {
        node_t *nod = list->head;
        int i=0;

        for (;i<position;i++)
        nod = nod->next;

        nod->prev->next = nod->next;
        nod->next->prev = nod->prev;

        free_node(nod);
        list->len--;

        return 0;
    }

    if (position > (list->len-1)/2)
    {
        node_t * nod = list->tail;
        int i=list->len-1;

        for(;i>position;i--)
        nod = nod->prev;

        nod->prev->next = nod->next;
        nod->next->prev = nod->prev;

        free_node(nod);
        list->len--;

        return 0;
    }

    return 0;
}

int insert_sorted_desc(list_t *list, int value) {

    node_t *nod = init_node(&value);

    if (list->len == 0)
    {
        list->head=list->tail=nod;
        list->len++;

        return 0;
    }

    if (*list->head->data < value) 
    {
        nod->next=list->head;
        list->head->prev = nod;
        list->head = nod;

        list->len++;

        return 0;
    }

    if (*list->tail->data > value)
    {
        nod->prev = list->tail;
        list->tail->next = nod;
        list->tail = nod;

        list->len++;

        return 0;
    }

    node_t *aux = list->tail;

    while (1)
    {
        if (*aux->data < value && *aux->prev->data >= value)
            break;
        aux=aux->prev;
    }

    nod->prev = aux->prev;
    nod->next = aux;
    nod->prev->next = nod;
    aux->prev = nod;

    list->len++;

    return 0;
}

list_t *remove_duplicates(list_t *list) {

    list_t *new_list = init_list();

    if (list->len == 0) return list;

    node_t *nod = list->head->next;
    insert_sorted_desc(new_list,*list->head->data);

    for (;nod!=NULL;nod=nod->next)
    {
        node_t *aux = new_list->head;
        int ok=1;

        for(;aux!=NULL;aux=aux->next)
            if(*aux->data == *nod->data)
            {
                ok=0;
                break;
            }

        if (ok) insert_sorted_desc(new_list,*nod->data);
    }

    return new_list;
}

/*int main()
{
    list_t *list = init_list();

    insert_node(list,6,0);
    insert_node(list,2,1);
    insert_node(list,4,1);

    print_list(list);

    insert_sorted_desc(list,3);
    insert_sorted_desc(list,3);

    print_list(list);

    list_t *new_list = remove_duplicates(list);

    print_list(new_list);
}*/