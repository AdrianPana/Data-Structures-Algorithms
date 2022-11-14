/**
 *  @author Florin Dumitrescu
 *
 *  Header pentru stack.c
 *  O stiva poate fi reprezentata printr-o lista simplu inlantuita
 *  pentru o complexitate de timp cat mai mica
 */

#ifndef SD_LABS_STACK_H
#define SD_LABS_STACK_H

typedef struct SNode {
    int nod;
    struct SNode *next;
} SNode_t;

typedef struct stack {
    SNode_t *top;
    SNode_t *len;
} stack_t;

SNode_t *initStackNode(int value);

stack_t *initStack();

/**
 * Adauga un element in stiva
 *
 * Complexitate temporala: O(1)
 *
 * @param stack stiva
 * @param value valoarea noului nod
 */
void push(stack_t *stack, int value);

/**
 * Elimina nodul din varful stivei
 *
 * @param stack stiva
 * @param status
 *          - STATUS_OK (0) daca operatia s-a efectuat cu succes
 *          - STATUS_ERR (1) altfel
 *
 * @return
 *      Valoarea nodului eliminat
 */
int pop(stack_t *stack);

/**
 * Afiseaza valoarea nodului din varful stivei
 *
 * @param stack stiva
 * @param status
 *          - STATUS_OK (0) daca operatia s-a efectuat cu succes
 *          - STATUS_ERR (1) altfel
 *
 * @return
 *      Valoarea nodului eliminat
 */
int top(stack_t *stack);

#endif //SD_LABS_STACK_H
