#include <bits/stdc++.h>
using namespace std;

#define cs string &

string LSC(cs, cs, cs);

int main() {
    string string1,string2,lsc;
    cin >> string1 >> string2;
    cout << LSC(string1,string2,lsc) << endl;
    return 0;
}

string LSC(cs string1, cs string2, string & lsc) {
    size_t numberOfString1 = string1.size();
    size_t numberOfString2 = string2.size();

    if (string1[numberOfString1-1] == string2[numberOfString2-1]) {
        lsc = string1[numberOfString1] + lsc;
    }

    string newString1 = string1.substr(0,numberOfString1-1);
    string newString2 = string2.substr(0,numberOfString2-1);
    if (!string1.empty() && !newStirng2.empty())
        LSC(string1,newString2,lsc);
    else
        return lsc;
}