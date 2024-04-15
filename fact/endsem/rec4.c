#include<stdio.h>
void nnumber(int n){
      if (n==0) 
      return;
     
      nnumber(n-1);
       printf("%d\n",n);
      return;
      }
int main()
{
      int n ;
      printf("enter the value of n:");
      scanf("%d",&n);
      nnumber(n);
      return 0;
}