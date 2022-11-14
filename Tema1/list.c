#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// initializeaza un nod cu valoarea value la momentul timestamp
node_t *init_node(double *value, int *timestamp)
{
    node_t *nod = malloc(sizeof(node_t));

    nod->next = NULL;
    nod->prev = NULL;

    nod->data = malloc(sizeof(double));
    *nod->data = *value;

    nod->timestamp = malloc(sizeof(int));
    *nod->timestamp = *timestamp;

    return nod;
}

// free la elementele nodului si la nodul in sine
void destroy_node(node_t *nod)
{
    free(nod->data);
    free(nod->timestamp);
    free(nod);

    return;
}

// initializeaza o structura de tip lista
list_t *init_list()
{
    list_t *list = malloc(sizeof(list_t));

    list->head = NULL;
    list->tail = NULL;

    list->len = 0;

    return list;
}
// distruge toate nodurile listei si ii da free
void destroy_list(list_t *list)
{
    while (list->len)
    {
        node_t *nod = list->tail;
        list->tail = list->tail->prev;

        destroy_node(nod);
        list->len--;
    }

    free(list);
}

// insereaza un nou nod in lista cu timestamp si valoare ca parametri
void insert_new_node(list_t *list, double value, int timestamp)
{
    // creez un nod nou
    node_t *nod = init_node(&value, &timestamp);

    // daca lista e goala, il adaug ca singurul nod
    if (list->len == 0)
    {
        list->head = list->tail = nod;
        list->len++;

        return;
    }

    // daca lista nu e goala, nodul se adauga la finalul acesteia
    nod->prev = list->tail;
    list->tail->next = nod;
    list->tail = nod;
    list->len++;

    return;
}
// parcurge nodurile listei pana la pozitia position si insereaza acolo un nou nod
void insert_node_at_pos(list_t *list, double data, int timestamp, int position)
{
    node_t *nod = init_node(&data, &timestamp);
    int i;
    node_t *aux = list->head;

    for (i = 0; i < position; i++)
    {
        aux = aux->next;
    }

    nod->next = aux->next;
    nod->prev = aux->prev;
    nod->next->prev = nod;
    nod->prev->next = nod;

    return;
}
// insereaza un nod dupa un nod transmis ca parametru
void insert_node_after_node(list_t *list, double data, int timestamp, node_t *nod)
{
    node_t *aux = init_node(&data, &timestamp);

    aux->prev = nod;
    aux->next = nod->next;
    nod->next = aux;
    aux->next->prev = aux;
    list->len++;

    return;
}

void print_list(list_t *list)
{
    printf("%d\n", list->len);

    node_t *nod = list->head;
    for (; nod != NULL; nod = nod->next)
        printf("%d %.2lf\n", *nod->timestamp, *nod->data);

    return;
}
