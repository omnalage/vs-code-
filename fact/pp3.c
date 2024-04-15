#include<stdio.h>
int factorial(int x)
{int fact=1;
for(int i=2;i<=x;i++)
{fact=fact*i;}
return fact;
}
int combination(int n, int r)
{int npr = factorial(n)/factorial(n-r);
return npr;
}
int main()
{
    int r,n;
    printf("enter the value of n:\n");
    scanf ("%d",&n);
    printf("enter the value of r:\n");
    scanf("%d",&r);
    int npr = combination(n,r);
    printf("%d",npr);
    return 0;
}