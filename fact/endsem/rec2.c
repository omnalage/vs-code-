#include<stdio.h>
void nnumber(int n){
      if (n==0) 
      return;
      printf("%d\n",n);
      nnumber(n-1);
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