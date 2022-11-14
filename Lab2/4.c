#include <stdio.h>

void swap(int *a,int *b)
{
    int aux=*a;
    *a=*b;
    *b=aux;
}

int partition(int *v,int pivot,int left,int right)
{
    int p=left;
    int u=right-1;

    while (1)
    {
        while (v[p]<pivot)
            p++;

        while (u>0 && v[u]>pivot)
            u--;

        if (p>=u) break;

        swap(&v[p],&v[u]);
    }
     return p;
    
}

void myQuickSort(int *v, int left, int right)
{
    if (left>=right) return;

    int index = partition(v,v[right],left,right);

    swap(&v[right],&v[index]);

    myQuickSort(v,left,index-1);
    myQuickSort(v,index+1,right);
}

int main()
{
    int i,n,v[100];

    scanf("%d",&n);
    for (i=0;i<n;i++)
    scanf("%d",&v[i]);

    myQuickSort(v,0,n-1);

    for (i=0;i<n;i++)
    printf("%d ",v[i]);

}