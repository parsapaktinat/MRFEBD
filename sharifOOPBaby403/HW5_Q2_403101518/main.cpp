#include <bits/stdc++.h>
using namespace std;

string LSC(const string &, const string &, int, int);

int main() {
    string string1,string2,lsc;
    cin >> string1 >> string2;

    int i = string1.size()-1, j = string2.size()-1;

    cout << LSC(string1,string2,i,j) << endl;
    return 0;
}

string LSC(const string &s1,const string &s2, int i, int j) {
    if (i < 0 || j < 0) {
        return "";
    }
    if (s1[i] == s2[j]) {
        return LSC(s1,s2,i-1,j-1) + s1[i];
    }
    else {
        string lsc1 = LSC(s1,s2,i-1,j);
        string lsc2 = LSC(s1,s2,i,j-1);
        return (lsc1.length() > lsc2.length()) ? lsc1 : lsc2;
    }
}