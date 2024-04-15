//nov 2022 Q1(b) 
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
void findClosestSumPair(int arr[], int n, int x) {
    if (n < 2) {
        printf("Array should have at least two elements.\n");
        return;
    }

    int closestSum = INT_MAX;
    int num1, num2;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int currentSum = arr[i] + arr[j];
            int currentDiff = abs(x - currentSum);

            if (currentDiff < closestSum) {
                closestSum = currentDiff;
                num1 = arr[i];
                num2 = arr[j];
            }
        }
    }

    printf("Closest sum pair: %d and %d\n", num1, num2);
}

int main() {
    int arr[] = {1, 4, 7, 9, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int targetSum = 14;

    findClosestSumPair(arr, size, targetSum);

    return 0;
}