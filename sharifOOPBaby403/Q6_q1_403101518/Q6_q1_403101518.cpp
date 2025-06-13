#include <bits/stdc++.h>

using namespace std;

string makeKey(const vector<int>& F, int start, int N) {
    string key = "";
    for (int i = 0; i < N; ++i)
        key += to_string(F[start + i]) + ",";
    return key;
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> F;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        F.push_back(x);
    }

    unordered_map<string, int> seen;
    int cycleStart = -1, cycleLen = -1;

    while (true) {
        string key = makeKey(F, F.size() - N, N);
        if (seen.count(key)) {
            cycleStart = seen[key];
            cycleLen = F.size() - cycleStart;
            break;
        }
        seen[key] = F.size();
        int next = 0;
        for (int i = F.size() - N; i < F.size(); ++i)
            next ^= F[i];
        F.push_back(next);
    }

    vector<int> prefixXor(F.size());
    prefixXor[0] = F[0];
    for (int i = 1;i < int(F.size());i++)
        prefixXor[i] = prefixXor[i - 1] ^ F[i];

    vector<int> cycleF;
    for (int i = 0;i < cycleLen;i++)
        cycleF.push_back(F[cycleStart + i]);

    vector<int> cyclePrefixXor(cycleLen);
    cyclePrefixXor[0] = cycleF[0];
    for (int i = 1;i < cycleLen;i++)
        cyclePrefixXor[i] = cyclePrefixXor[i - 1] ^ cycleF[i];

    while (Q--) {
        long long K;
        cin >> K;
        K--;
        if (K < (int)F.size()) {
            cout << prefixXor[K] << '\n';
        }
        else {
            long long dist = K - cycleStart;
            int posInCycle = dist % cycleLen;
            int result = prefixXor[cycleStart - 1] ^ cyclePrefixXor[posInCycle];
            cout << result << '\n';
        }
    }
}
