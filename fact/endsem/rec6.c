#include<stdio.h>
int power(int a, int b){
      if(b==0) return 1;
      return a*power(a,b-1);

}

int main()
{
      int a,b;
      printf("enter the base a:");
      scanf("%d",&a);
      printf("enter the power b:");
      scanf("%d",&b);
      int p= power(a,b);
      printf("%d raised to power %d is %d",a,b,p);
      return 0;
}