#include <stdio.h>

int fibo(int k)
{
    if (k<2) return 1;

    else return fibo(k-1)+fibo(k-2);
}

int fun(int i)  {
  if (i%2 != 0) return i;
  else return fun(fun(i - 1)); 
}

int main()
{
    int n;

    scanf ("%d",&n);

    printf("%d",fun(18));
}