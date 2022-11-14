#include <stdio.h>

int foo(int *v,int left,int right)
{
    if (left>right) return 0;
    if (left==right)
    {
        if (left%2==0) return v[left];
        else return 0;
    }

    else
    {
        int mid=(left+right)/2;
        return foo(v,left,mid)+foo(v,mid+1,right);
    }
}

int main()
{
    int v[100],i,n;

    scanf("%d",&n);
    for (i=0;i<n;i++)
    scanf("%d",&v[i]);

    printf("%d\n",foo(v,0,n-1));
}

