#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"

#define K 5
#define K2 3

void swap(double *a, double *b)
{
    double aux = *a;
    *a = *b;
    *b = aux;
}
// max1 > max2 > max3
// functia primeste o valoare noua si modifica valorile maximelor dupa caz
// stage reprezinta numarul de valori max initializate
void assign_max(double value, double *max1, double *max2, double *max3, int *stage)
{
    if (*stage == 0)
    {
        *max1 = value;

        (*stage)++;
        return;
    }

    if (*stage == 1)
    {
        *max2 = value;
        if (*max1 < *max2)
            swap(max1, max2);

        (*stage)++;
        return;
    }

    if (*stage == 2)
    {
        *max3 = value;
        if (*max2 < *max3)
            swap(max2, max3);
        if (*max1 < *max2)
            swap(max1, max2);

        (*stage)++;
        return;
    }

    if (*max1 <= value)
    {
        *max3 = *max2;
        *max2 = *max1;
        *max1 = value;
    }
    else if (*max2 <= value)
    {
        *max3 = *max2;
        *max2 = value;
    }
    else if (*max3 <= value)
    {
        *max3 = value;
    }
}

list_t *e1(list_t *list)
{
    double average, deviation, sum;
    node_t *first_node = list->head;
    int i, j;

    list_t *aux_list = init_list();
    insert_new_node(aux_list, *list->head->data, *list->head->timestamp);
    insert_new_node(aux_list, *list->head->next->data, *list->head->next->timestamp);

    for (i = 0; i < list->len - K + 1; i++)
    {
        average = deviation = sum = 0;

        // aleg nodul de pornire al ferestrei
        node_t *aux = first_node;

        // parcurg nodurile ferestrei si le adun la suma
        for (j = 0; j < K; j++)
        {
            sum += *aux->data;
            deviation += (*aux->data) * (*aux->data);
            aux = aux->next;
        }

        // impart suma la K pentru a afla media
        average = sum / K;

        // formula deviatiei daca scriu desfasurat formula
        deviation = sqrt((deviation - 2 * sum * average + K * average * average) / K);

        node_t *mid_node = first_node->next->next;

        //daca nodul este conform criteriului il adaug in lista noua
        if ((*mid_node->data > average - deviation) && (*mid_node->data < average + deviation))
        {
            insert_new_node(aux_list, *mid_node->data, *mid_node->timestamp);
        }

        first_node = first_node->next;
    }

    insert_new_node(aux_list, *list->tail->prev->data, *list->tail->prev->timestamp);
    insert_new_node(aux_list, *list->tail->data, *list->tail->timestamp);

    destroy_list(list);

    return aux_list;
}

list_t *e2(list_t *list)
{
    node_t *nod = list->head;
    list_t *aux_list = init_list();
    int i;

    for (i = 0; i < list->len - K + 1; i++)
    {
        node_t *aux = nod;
        int j, stage = 0;
        double max1 = 0, max2 = 0, max3 = 0;

        //aflu cele mai mari 3 valori din fereastra
        for (j = 0; j < K; j++)
        {
            assign_max(*aux->data, &max1, &max2, &max3, &stage);

            aux = aux->next;
        }

        //a treia cea mai mare este valoarea mediana, care este adaugata in lista noua
        insert_new_node(aux_list, max3, *nod->next->next->timestamp);

        nod = nod->next;
    }

    destroy_list(list);

    return aux_list;
}

list_t *e3(list_t *list)
{
    node_t *nod = list->head;
    list_t *aux_list = init_list();
    int i;

    for (i = 0; i < list->len - K + 1; i++)
    {
        node_t *aux = nod;
        int j;
        double s = 0;
        for (j = 0; j < K; j++)
        {
            s += *aux->data;

            aux = aux->next;
        }

        s /= K;

        insert_new_node(aux_list, s, *nod->next->next->timestamp);

        nod = nod->next;
    }

    destroy_list(list);

    return aux_list;
}

list_t *u(list_t *list)
{
    node_t *nod = list->head;

    for (; nod->next != NULL; nod = nod->next)
    {
        if (abs(*nod->timestamp - *nod->next->timestamp) >= 100 && abs(*nod->timestamp - *nod->next->timestamp) <= 1000)
        {
            *nod->next->timestamp = (*nod->timestamp + *nod->next->timestamp) / 2;
            *nod->next->data = (*nod->data + *nod->next->data) / 2;
        }
    }

    return list;
}

list_t *c(list_t *list)
{
    node_t *nod = list->head;
    double C;

    for (; nod->next != NULL; nod = nod->next)
    {
        if (abs(*nod->timestamp - *nod->next->timestamp) > 1000)
        {
            int t;
            int t1 = *nod->timestamp;
            int t2 = *nod->next->timestamp;
            int r = *nod->next->next->next->timestamp;
            double new_data;

            node_t *last_node = nod;
            node_t *left = nod->prev->prev;
            node_t *right = nod->next->next->next;

            double sum = 0, sum1 = 0, sum2 = 0;
            int j;

            // calculez numitorul fractiei lui w(i,k)
            for (j = 0; j < K2; j++)
                sum += ((double)j / (K2 - 1)) * ((double)j / (K2 - 1)) * 0.9 + 0.1;

            // calculez w(i,k) si il folosesc pentru a construi cele doua sume
            // acestea pot fi precalculate pentru a putea fi folosite direct in formula noii valori
            for (j = 0; j < K2; j++)
            {
                double w = (((double)j / (K2 - 1)) * ((double)j / (K2 - 1)) * 0.9 + 0.1) / sum;

                sum1 += *left->data * w;
                sum2 += *right->data * w;

                left = left->next;
                right = right->prev;
            }

            for (t = t1 + 200; t < t2; t = t + 200)
            {
                double up = t - t1;
                double down = t2 - t1;

                //calculez C si il folosesc in formula pentru a afla noua valoare
                C = up / down;

                new_data = (1 - C) * sum1 + C * sum2;

                insert_node_after_node(list, new_data, t, last_node);

                last_node = last_node->next;
            }
        }
    }

    return list;
}

//folosita pentru 2.5, incrementeaza "frecventa" unui interval
void update_node(list_t *list, int pos)
{
    node_t *nod = list->head;

    int i;
    for (i = 0; i < pos; i++)
        nod = nod->next;

    (*nod->data)++;

    return;
}

void *st(list_t *list, int delta)
{
    list_t *fr_list = init_list();

    double min, max;
    min = *list->head->data;
    max = *list->head->data;

    node_t *nod = list->head->next;

    //aflu cea mai mica si mai mare valori din lista
    for (; nod != NULL; nod = nod->next)
    {
        if (min > *nod->data)
            min = *nod->data;
        if (max < *nod->data)
            max = *nod->data;
    }

    // aflu captele celor mai indepartate intervale
    int l_bound, h_bound;
    l_bound = ((int)(min / delta - 1) * delta);
    h_bound = (((int)(max / delta) + 1) * delta);

    //creez cate un nod in lista de "frecventa" pentru a stoca un interval
    int i;
    for (i = l_bound; i < h_bound; i += delta)
    {
        insert_new_node(fr_list, 0, i);
    }

    //parcurg lista si daca un nod se afla intr-un interval, cresc valoarea corespunzatoare in lista de "frecventa"
    for (nod = list->head; nod != NULL; nod = nod->next)
    {
        int pos = 0;
        for (i = l_bound; i < h_bound; i += delta)
        {
            if (*nod->data >= i && *nod->data < i + delta)
                update_node(fr_list, pos);
            pos++;
        }
    }

    for (nod = fr_list->head; nod != NULL; nod = nod->next)
    {
        if (*nod->data != 0)
        {
            int fr = (int)*nod->data;
            printf("[%d, %d] %d\n", *nod->timestamp, (*nod->timestamp) + delta, fr);
        }
    }

    destroy_list(fr_list);

    return;
}