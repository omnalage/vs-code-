#include<stdio.h>
int stairs(int n){
      if(n==1 || n==2 || n ==3) return n;
      return  stairs(n-1)+ stairs(n-2);
        
}
int main()
{
      int n ;
      printf("enter the value of n:");
      scanf("%d",&n);
      int wyas = stairs(n);
      printf("%d",wyas);
      return 0;
}