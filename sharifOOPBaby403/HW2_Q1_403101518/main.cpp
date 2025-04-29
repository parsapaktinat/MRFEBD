#include <bits/stdc++.h>

using namespace std;

int numberOfDigits(long long);
long long inversOfNumber(long long);
long long findBiggestNumber(long long);
void sorter(long long digits[],int n);

int main() {
    long long number,numberInvers;
    cin >> number;
    number = findBiggestNumber(number);
    numberInvers = inversOfNumber(number);
    cout << number + numberInvers;
    return 0;
}

int numberOfDigits(long long n) {
    int Ndigits = 0;
    while (n != 0) {
        n /= 10;
        Ndigits++;
    }
    return Ndigits;
}

long long inversOfNumber(long long n) {
    long long result = 0;
    int digits = numberOfDigits(n);
    digits--;
    while (n != 0) {
        result += n % 10;
        result *= 10;
        n /= 10;
    }
    result /= 10;
    return result;
}

long long findBiggestNumber(long long n) {
    int nDigits = numberOfDigits(n);
    long long digits[nDigits];
    int index = 0;
    while (n != 0) {
        digits[index] = n % 10;
        index++;
        n /= 10;
    }
    long long result = 0;
    sorter(digits,nDigits);
    for (int i = nDigits - 1;i >= 0;i--) {
        result += digits[nDigits - 1 - i];
        result *= 10;
    }
    result /= 10;
    return result;
}

void sorter(long long digits[],int n) {
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < i;j++) {
            if (digits[i] > digits[j]) {
                long long temp = digits[i];
                digits[i] = digits[j];
                digits[j] = temp;
            }
        }
    }
}