#ifndef LIST_H
#define LIST_H

typedef struct node {
    double *data;
    int *timestamp;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct list {
    node_t *head;
    node_t *tail;
    int len;
} list_t;

node_t * init_node(double *value, int *timestamp);

list_t *init_list();

void print_list(list_t * list);

void insert_new_node(list_t *list, double value, int timestamp);

void insert_node_at_pos(list_t *list, double data, int timestamp, int position);

void insert_node_after_node(list_t *list, double data, int timestamp, node_t * nod);

void add_node(list_t *list, node_t * nod);

void destroy_node(node_t * nod);

void destroy_list(list_t * list);
#endif