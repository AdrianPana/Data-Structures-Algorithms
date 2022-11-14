#include <stdio.h>
#include <math.h>

float new_log2(float n,int prec,float left,float right)
{
    float mid = (left+right)/2;
    float rez = pow(2,mid);

    float precision = pow(10,-prec);

    if (fabs(rez-n)<=precision) return mid;

    else if (rez-n >= precision) return new_log2(n,prec,left,mid);
    else if (n-rez >= precision) return new_log2(n,prec,mid,right);
}

int main()
{
    float n;
    int prec;

    scanf("%f%d",&n,&prec);

    printf("%f\n",new_log2(n,prec,0,n));

    return 0;

}