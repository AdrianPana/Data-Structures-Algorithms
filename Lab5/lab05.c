#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab05.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

#define NUM_QUEUES 10

int checkBalancedBrackets(char *exp) {
    
    stack_t * stack = initList();
    int status;

    int i;
    for (i=0;i<strlen(exp);i++)
    {
        if(exp[i]=='(' || exp[i]=='[' || exp[i]=='{')
        push(stack,exp[i]);

        else 
        {
            switch(exp[i])
            {
                case ')': 
                    if(top(stack,&status)!='(') return 0;
                    pop(stack,&status);
                    break;
                
                case ']': 
                    if(top(stack,&status)!='[') return 0;
                    pop(stack,&status);
                    break;

                case '}': 
                    if(top(stack,&status)!='{') return 0;
                    pop(stack,&status);
                    break;
                
            }
        }
    }

    if (stack->len!=0) return 0;

    return 1;
}

void radixSort(int *v, int n) {
    
    queue_t *x[10];
    

    int max_digits=0;
    int i,status;

    for (i=0;i<10;i++)
    x[i]=initList();

    for (i=0;i<n;i++)
    {
        int nr_c=0;
        int c=v[i];

        while(c!=0)
        {
            nr_c++;
            c=c/10;
        }
        if (nr_c>max_digits) max_digits=nr_c;
    }

    int p=1;
    

    for (i=0;i<=max_digits;i++)
    {
        int index=0;

        int j;
        for (j=0;j<n;j++)
        {
            enqueue(x[v[j]/p%10],v[j]);
        }

        for (j=0;j<10;j++)
        {
            while(x[j]->len!=0)
            {
                v[index]=dequeue(x[j],&status);
                index++;
            }
        }
        p*=10; 
    }
    return;
}
