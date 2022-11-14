#include <stdio.h>
#include <stdlib.h>

#include "lab03.h"

void print_list_int(sl_list_t *list)
{
    node_t *aux = list->head;

    printf("%-20s", "Lista construita:");

    while (aux->next != NULL) {
        printf("%d->", *aux->data);
        aux = aux->next;
    }
    printf("%d\n", *aux->data);
}

node_t *init_node(const int *value)
{
    node_t *nod = malloc(sizeof(node_t));

    nod->data = malloc(sizeof(int));
    nod->data = *value;
    nod->next = NULL;

    return nod;
}

void free_node(node_t *node)
{
    node->next=NULL;
    free(node->data);
    free(node);

    return;
}

sl_list_t *init_list()
{
    sl_list_t * list = malloc(sizeof(sl_list_t));

    list->head=NULL;
    list->tail=NULL;
    list->len = 0;
    
    return list;
}

void destroy_list(sl_list_t *list)
{
    if (list->len!=0)
    {
        int i;
        node_t *nod = list->head;
        node_t *aux_nod;

        for (i=0;i<list->len-1;i++)
        {   
            aux_nod=nod->next;
            free_node(nod);
            nod = aux_nod;
        }

        free_node(nod);
    }

    free(list);
}

int insert_node(sl_list_t *list, int value, size_t position)
{
    if (list->len <= position || position < 0) return -1;

    node_t * nod = init_node(value);

    if (position == 0)
    {
        nod->next=list->head;
        list->head=nod;
    }

    else if (position == list->len-1)
    {
        nod->next=NULL;
        list->tail->next=nod;
        list->tail=nod;
    }

    else 
    {
        int i;
        node_t *aux_nod = list->head;

        for (i=0;i<position-1;i++)
        {
            aux_nod = aux_nod->next;
        }

        nod->next = aux_nod->next;
        aux_nod->next = nod;
    }

    list->len++;

    return 0;
}

int remove_node_by_key(sl_list_t *list, int value)
{
    node_t * nod = list->head;
    node_t * prev = nod;

    while (nod->data != value && nod->next!=NULL)
    {
        prev = nod;
        nod = nod->next;
    }

    if (nod->next == NULL && nod->data!=value) return -1;

    if (nod == list->head)
    {
        list->head = nod->next;
        free_node(nod);

        return 0;
    }

    prev->next=nod->next;
    free_node(nod);

    list->len--;

    return 0;
}

int remove_node_at_position(sl_list_t *list, size_t position)
{
    if (list->len <= position || position < 0) return -1;

    if(position==0)
    {
        list->head=list->head->next;
        free_node(list->head);

        list->len--;

        return 0;
    }

    int i;
    node_t *nod = list->head;

    for (i=0;i<position-1;i++)
    {
        nod=nod->next;
    }

    node_t * aux = nod->next;
    nod->next=aux->next;
    free_node(aux);

    list->len--;

    return 0;
}

int cyclic_search(sl_list_t *list, int k)
{
    k = k%list->len;

    node_t * nod = list->head;
    int i;

    for (i=0;i<k;i++)
    nod=nod->next;

    return nod->data;
}

int main()
{
    sl_list_t * list = init_list();
    insert_node(list,1,0);
    printf("%d\n",cyclic_search(list,0));

    return 0;
}