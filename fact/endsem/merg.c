#include <stdio.h>
// int swap(int *a,int *b){
//     int t= *a;
//     *a=*b;
//     *b=t;
// }
void mergeself(int a[], int low, int mid, int high) {
    int i, j, k, size;
    i = low;
    j = mid + 1;
    k = 0;
    size = high - low + 1;
    int c[size];
    while ((i <= mid) && (j <= high)) {
        if (a[i] < a[j]) {
            c[k] = a[i];
            k++;
            i++;
        } else {
            c[k] = a[j];
            k++;
            j++;
        }
    }
  
        while (i <= mid) {
            c[k] = a[i];
            k++;
            i++;
        }
        
        while (j <= high) {
            c[k] = a[j];
            k++;
            j++;
        }
    
    for (k = 0; k < size; ++k, ++low) {
        a[low] = c[k];
    }
}


void Mergesort(int a[], int low, int high){
    int mid;
    if (low<high){
       mid=low+(high-low)/2;
        Mergesort(a,low,mid);
        Mergesort(a,mid+1,high);
        mergeself(a,low,mid,high);
    }

}

void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

int main() {
  int data[] = {8, 7, 2, -1, 0, 9, 6};
  
  int n = sizeof(data) / sizeof(data[0]);
  
  printf("Unsorted Array\n");
  printArray(data, n);
  
  Mergesort(data, 0, n - 1);
  
  printf("Sorted array in ascending order: \n");
  printArray(data, n);
}
