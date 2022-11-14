#include <stdio.h>

void afisare(int *v, int k)
{
    int i;
    for (i=0;i<k;i++)
    printf("%d ",v[i]);
    printf("\n");
}

void bkt(int k,int n,int *v)
{
    if (n==0) {   afisare(v,k);
    return;}


    int i;
    for (i=n;i>0;i--)
    {
        if (v[k-1]>=i) 
        {   
            v[k]=i;
            k++;
            bkt(k,n-i,v);
            k--;
        }
    }
    
}

int main()
{
    int n,v[100];

    scanf("%d",&n);
    bkt(0,n,v);

}