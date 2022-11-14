#include <stdlib.h>
#include "stack.h"


SNode_t *initStackNode(int value) {
    SNode_t *newNode = malloc(sizeof(SNode_t));
    newNode->nod = value;
    newNode->next = NULL;

    return newNode;
}

stack_t *initStack() {
    stack_t *newStack = malloc(sizeof(stack_t));
    newStack->top = NULL;
    newStack->len = 0;

    return newStack;
}

void push(stack_t *stack, int value) {

    SNode_t *new_node = initStackNode(value);

    new_node->next = stack->top;
    stack->top = new_node;
    ++stack->len;
}

int pop(stack_t *stack) {
    SNode_t *aux = stack->top;
    int ret;

    if (stack->len == 0) {
        // Stiva e goala
        return -1;
    }

    // Salvez valoarea nodului
    ret = aux->nod;

    // Elimin nodul din stiva
    stack->top = aux->next;
    --stack->len;

    free(aux);

    return ret;
}

int top(stack_t *stack) {
    if (stack->len == 0) {
        return -1;
    }
    return stack->top->nod;
}
