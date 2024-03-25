#include <stdio.h>

// Function declaration
int factorial(int n);

int main() {
    int num ;
    printf("enter the element:");
    scanf("%d",&num);
    int result = factorial(num);
    printf("Factorial of %d = %d\n", num, result);
    return 0;
}

// Function definition
int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}
