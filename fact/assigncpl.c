#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

typedef struct BigInteger {
    int arr[MAX_SIZE];
    int size;
} BigInt;

BigInt input() {
    printf("Enter the number: ");
    char s[MAX_SIZE];
    scanf("%s", s);

    int isNegative = 0;
    if (s[0] == '-') {
        isNegative = 1;
        memmove(s, s + 1, strlen(s));
    }

    int length = strlen(s);
    BigInt k;
    int z = 0;
    for (int i = length - 1; i >= 0; i--) {
        k.arr[z] = s[i] - '0';
        z++;
    }
    k.size = z;

    if (isNegative) {
        for (int i = 1; i < k.size; i++) {
            k.arr[i] = -k.arr[i];
        }
    }

    return k;
}

void printBigInt(BigInt k) {
    for (int i = k.size - 1; i >= 0; i--) {
        printf("%d", k.arr[i]);
    }
    printf("\n");
}

BigInt add(BigInt a, BigInt b) {
    BigInt ans;
    int carry = 0;
    int i = 0;
    while (i < a.size || i < b.size || carry) {
        int sum = carry;
        if (i < a.size) sum += a.arr[i];
        if (i < b.size) sum += b.arr[i];
        ans.arr[i] = sum % 10;
        carry = sum / 10;
        i++;
    }
    ans.size = i;
    return ans;
}

BigInt multiply(BigInt a, BigInt b) {
    BigInt ans;
    memset(ans.arr, 0, sizeof(ans.arr));
    for (int i = 0; i < a.size; i++) {
        for (int j = 0, carry = 0; j < b.size || carry; j++) {
            int product = ans.arr[i + j] + a.arr[i] * (j < b.size ? b.arr[j] : 0) + carry;
            ans.arr[i + j] = product % 10;
            carry = product / 10;
        }
    }
    int i = MAX_SIZE - 1;
    while (i >= 0 && ans.arr[i] == 0) i--;
    ans.size = i + 1;
    return ans;
}

BigInt subtract(BigInt a, BigInt b) {
    BigInt ans;
    memset(ans.arr, 0, sizeof(ans.arr));
    int borrow = 0;
    for (int i = 0; i < a.size; i++) {
        int sub = a.arr[i] - borrow;
        if (i < b.size) sub -= b.arr[i];
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        ans.arr[i] = sub;
    }
    int i = MAX_SIZE - 1;
    while (i >= 0 && ans.arr[i] == 0) i--;
    ans.size = i + 1;
    return ans;
}

int main() {
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
