#include<stdio.h>
int main()
{
    int r,n;
    printf("enter the value of n:\n");
    scanf ("%d",&n);
    printf("enter the value of r:\n");
    scanf("%d",&r);
n = n+r;
r = n-r;
n = n-r;
printf("the value of n is %d\n",n);
printf("the value of r is %d",r);
return 0;
}
