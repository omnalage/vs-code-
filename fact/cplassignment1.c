#include <stdio.h>
#include <string.h>

typedef struct BigInteger
{
    int arr[1000];
    int size;
} BigInt;

BigInt input()
{
    printf("Enter the number: ");
    char s[10000];
    scanf("%s", s);

    int isNegative = 0;
    if (s[0] == '-')
    {
        isNegative = 1;
        memmove(s, s + 1, strlen(s));
    }

    int length = strlen(s);
    BigInt k;
    int z = 0;
    for (int i = length - 1; i >= 0; i--)
    {
        k.arr[z] = s[i] - '0';
        z++;
    }
    k.size = z;

    if (isNegative)
    {
        for (int i = 1; i < k.size; i++)
        {
            k.arr[i] = -k.arr[i];
        }
    }

    return k;
}

void printBigInt(BigInt k)
{
    for (int i = k.size - 1; i >= 0; i--)
    {
        printf("%d", k.arr[i]);
    }
    printf("\n");
}

BigInt subtract(BigInt a, BigInt b)
{
    BigInt ans;
    if (a.size < b.size)
    {
        return subtract(b, a);
    }
    else if (a.size == b.size)
    {
        int i = a.size - 1;
        while (i >= 0 && a.arr[i] == b.arr[i])
        {
            i--;
        }
        if (i == -1)
        {
            ans.arr[0] = 0;
            ans.size = 1;
            return ans;
        }
        if (a.arr[i] < b.arr[i])
        {
            return subtract(b, a);
        }
    }

    int z = 0;
    int j = 0;
    for (int i = 0; i < b.size; i++)
    {
        if (a.arr[i] - b.arr[i] < 0)
        {
            a.arr[i + 1]--;
            a.arr[i] += 10;
        }
        ans.arr[z] = a.arr[i] - b.arr[i];
        if (ans.arr[z] != 0)
        {
            j = i;
        }
        z++;
    }

    for (int i = b.size; i < a.size; i++)
    {
        if (a.arr[i] != 0)
        {
            j = i;
        }
        if (a.arr[i] < 0)
        {
            a.arr[i + 1]--;
            a.arr[i] += 10;
        }
        ans.arr[z] = a.arr[i];
        z++;
    }
    ans.size = j + 1;
    return ans;
}

BigInt add(BigInt a, BigInt b)
{
    if (a.size < b.size)
    {
        return add(b, a);
    }

    BigInt ans;
    int z = 0;
    int c = 0;
    for (int i = 0; i < b.size; i++)
    {
        int temp = a.arr[i] + b.arr[i] + c;
        ans.arr[z] = temp % 10;
        c = temp / 10;
        z++;
    }
    for (int i = b.size; i < a.size; i++)
    {
        int temp = a.arr[i] + c;
        ans.arr[z] = temp % 10;
        c = temp / 10;
        z++;
    }
    if (c > 0)
    {
        ans.arr[z] = c;
        z++;
    }
    ans.size = z;
    return ans;
}

BigInt multiply(BigInt a, BigInt b)
{
    BigInt ans;
    ans.size = 0;
    for (int i = 0; i < a.size; i++)
    {
        int c = 0;
        BigInt t;
        int z = 0;
        for (int j = 0; j < b.size; j++)
        {
            int temp = a.arr[i] * b.arr[j] + c;
            t.arr[z] = temp % 10;
            c = temp / 10;
            z++;
        }
        if (c > 0)
        {
            t.arr[z] = c;
            z++;
        }
        t.size = z;
        BigInt pro1;
        int ind = 0;
        for (int p = 0; p < i; p++)
        {
            pro1.arr[ind] = 0;
            ind++;
        }

        for (int p = 0; p < t.size; p++)
        {
            pro1.arr[ind] = t.arr[p];
            ind++;
        }
        pro1.size = ind;
        ans = add(ans, pro1);
    }
    return ans;
}

int main()
{
    BigInt a = input();
    printf("BigInt a: ");
    printBigInt(a);

    BigInt b = input();
    printf("BigInt b: ");
    printBigInt(b);

    BigInt result = multiply(a, b);
    printf("BigInt multiply: ");
    printBigInt(result);

    result = subtract(a, b);
    printf("BigInt subtract: ");
    printBigInt(result);

    result = add(a, b);
    printf("BigInt add: ");
    printBigInt(result);

    return 0;
}
