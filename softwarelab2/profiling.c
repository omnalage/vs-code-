#include<stdio.h>

int recursive_fib(int x)
{
    if (x==0 || x==1)
    {
        return 1;
    }
    
    return x*recursive_fib(x-1);
}

int iterative_fib(int x)
{
    if (x==0 || x==1)
    {
        return 1;
    }
    int res=1;
    for (int i = x; i > 1; i--)
    {
        res=res*i;
    }
    return res;
}

int main()
{
    int a=4;
    int res=recursive_fib(a);
    printf("Value of factorial of 4 using recursive function: %d\n",res);
    res=iterative_fib(a);
    printf("Value of factorial of 4 using iterative function: %d\n",res);
    return 0;
}