#include <bits/stdc++.h>
using namespace std;

#define cs string &

string LSC(cs, cs);

int main() {

    return 0;
}

string LSC(cs string1, cs string2, string & lsc) {
    size_t numberOfString1 = string1.size();
    size_t numberOfString2 = string2.size();

    if (string1[numberOfString1-1] == string2[numberOfString2-1]) {
        lsc = string1[numberOfString1] + lsc;
    }

    string1.pop_back();
    string2.pop_back();
    if (!string1.empty() && !string2.empty()) {
        LSC(string1,string2,lsc);
    }

    return lsc
}