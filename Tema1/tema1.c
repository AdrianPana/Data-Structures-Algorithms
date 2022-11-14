#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "list.h"
#include "procedures.h"

#define K 5
#define K2 3
#define precision 0.01

void citire_date(list_t *list, int *nr_perechi)
{
    scanf("%d", nr_perechi);

    int i, timestamp;
    double data;

    for (i = 0; i < *nr_perechi; i++)
    {
        scanf("%d %lf", &timestamp, &data);
        insert_new_node(list, data, timestamp);
    }
}

char *citire_cmd(char *v)
{
    char *aux;
    strcpy(aux, v + 2);
    strcpy(v, aux);

    return v;
}

int main(int argc, char *argv[])
{
    int nr_perechi;
    int stats_shown = 0;
    list_t *list = init_list();

    citire_date(list, &nr_perechi);

    int i;
    for (i = 1; i < argc; i++)
    {
        char *cmd = argv[i] + 2;

        if (strcmp(cmd, "e1") == 0)
            list = e1(list);
        else if (strcmp(cmd, "e2") == 0)
            list = e2(list);
        else if (strcmp(cmd, "e3") == 0)
            list = e3(list);
        else if (strcmp(cmd, "u") == 0)
            list = u(list);
        else if (strcmp(cmd, "c") == 0)
            list = c(list);
        else if (strstr(cmd, "st"))
        {
            stats_shown = 1;

            char *s_delta = cmd + 2;
            int delta = 0, j;

            for (j = 0; j < strlen(s_delta); j++)
                delta = delta * 10 + (s_delta[j] - '0');

            st(list, delta);
        }
    }

    if (!stats_shown)
        print_list(list);

    destroy_list(list);

    return 0;
}