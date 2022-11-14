#include <stdio.h>

int binarySearch(int *v, int x, int left, int right)
{
    if (left>right) return 0;

    if (left == right && v[left] == x) return 1; 

    int mid = (left+right)/2;

    if (x==v[mid]) return 1;
    else 
    {
        if (x<v[mid]) return binarySearch(v,x,left,mid);
        else return binarySearch(v,x,mid+1,right);
    }
}

int main()
{
    int v[100],x,n;

    scanf("%d%d",&n,&x);

    int i;
    for (i=0;i<n;i++)
    scanf("%d",&v[i]);

    if (binarySearch(v,x,0,n))
        printf("x se afla in vector\n");
    else printf("x nu se afla in vector\n");

    return 0;
}