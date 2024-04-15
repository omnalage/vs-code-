// 2022 3(a)
#include <stdio.h>
int partition(int a[], int s, int e)
{
    int p = a[e];
    int i = s - 1, j;
    for (j = s; j <=e-1; j++)
    {
        if (a[j] < p)
        {
            i++;
            int t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    i++;
    int t = a[i];
    a[i] = a[j];
    a[j] = t;
    return i;
}
int quick(int a[], int s, int e, int k)
{
    if (s <= e)
    {
        int p = partition(a, s, e);
        if (p == k)
        {
            return p;
        }
        else if (p > k)
        {
            return quick(a, s, p-1, k);
        }
        else
        {
            return quick(a, p + 1, e, k);
        }
    }
    else
        return -1;
}
void median(int a[], int n)
{
    if (n % 2 == 0)
    {
        int m1 = quick(a, 0, n - 1, n / 2 - 1);
        int m2 = quick(a, 0, n - 1, n / 2);
        printf("medians are: %d and %d", a[m1], a[m2]);
    }
    else
    {
        int m = quick(a, 0, n - 1, n / 2);
        printf("median is %d", a[m]);
    }
}
int main()
{
    int a[] = {6, 3, 2, 9, 4, 5};
    int n = 6;
    int b[n];
    for (int i = 0; i < n; i++)
    {
        b[i] = a[i];
    }

    median(b, n);
}