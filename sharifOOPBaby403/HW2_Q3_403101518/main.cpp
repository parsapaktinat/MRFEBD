#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    int n,m,tempN,index = 0;
    int *p;

    size_t nElements = 0;

    while (s != "exit") {
        cin >> s;
        if (s == "insert") {
            cin >> n;
            if (nElements == 0) {
                nElements++;
                p = (int*)malloc(sizeof(int));
                index = 0;
                p[index] = n;
            }
            else {
                nElements++;
                index = nElements - 1;
                p = (int*)realloc(p,nElements*sizeof(int));
                p[index] = n;
            }
        }
        else if (s == "pop") {
            cin >> n;
            if ((nElements <= 0) || (n < 0) || (n >= nElements))
                continue;
            nElements--;
            for (int i = n;i < nElements;i++) {
                tempN = p[i];
                p[i] = p[i+1];
                p[i+1] = tempN;
            }
            p = (int*)realloc(p,nElements*sizeof(int));
        }
        else if (s == "swap") {
            cin >> n >> m;
            if ((n >= nElements) || (m >= nElements) || (n < 0) || (m < 0))
                continue;
            tempN = p[m];
            p[m] = p[n];
            p[n] = tempN;
        }
        else if (s == "print") {
            if (nElements <= 0) {
                continue;
            }
            for (int i = 0;i < nElements;i++) {
                cout << p[i] << " ";
            }
            cout << endl;
        }
        else if (s == "exit") {
            free(p);
            break;
        }
        index = nElements - 1;
    }
}