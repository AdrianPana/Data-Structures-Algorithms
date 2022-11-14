#include <stdio.h>

int cifre (int n, int x)
{
    if (n<10)
        {
            if (n<x) return 1;
            return 0;
        }

    else 
    {
        if (n%10<x) return 1+cifre(n/10,x);
        else return cifre (n/10,x);
    }
}

int main()
{
    int n,x;

    scanf("%d%d",&n,&x);

    printf("%d\n",cifre(n,x));
}