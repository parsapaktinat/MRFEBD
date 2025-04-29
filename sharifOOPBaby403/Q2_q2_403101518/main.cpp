#include <bits/stdc++.h>
using namespace std;

int main() {
    int *p = new int[200000];
    int n,counter = 0;
    cin >> n;
    for (int i = 0;i < n;i++) {
        cin >> p[i];
    }
    for (int i = 0;i < n;i++) {
        for (int j = i;j < n;j++) {
            if (p[j] < p[i])
                counter++;
        }
    }
    cout << counter%100000;
    return 0;
}
