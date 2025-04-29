#include <bits/stdc++.h>

using namespace std;

int main() {
    int a,b,c;
    cin >> a >> b >> c;

    if ((a+b > c)&&(a+c > b)&&(b+c > a)&&(abs(a-b) < c)&&(abs(a-c) < b)&&(abs(b-c) < a)) {
        cout << "True";
    }
    else {
        cout << "False";
    }

    return 0;
}