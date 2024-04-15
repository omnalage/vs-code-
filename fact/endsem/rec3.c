#include<stdio.h>
void nnumber(int x,int n){
      if (x>n) 
      return;
      printf("%d\n",x);
      nnumber(x+1,n);
      return;
      }
int main()
{
      int n ;
      printf("enter the value of n:");
      scanf("%d",&n);
      nnumber(1,n);
      return 0;
}