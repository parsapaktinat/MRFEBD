#include <bits/stdc++.h>
using namespace std;

void merge(vector<char>& str, int l, int m, int r);
void mergeSort(vector<char>& arr, int l, int r);
string sorting(const string& str);

int main() {
    int n;
    cin >> n;
    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }

    unordered_map<string, vector<string>> sameWordGroup;
    vector<string> order;

    for (const string& s : strings) {
        string refrenceString = sorting(s);
        if (sameWordGroup.find(refrenceString) == sameWordGroup.end()) {
            order.push_back(refrenceString);
        }
        sameWordGroup[refrenceString].push_back(s);
    }

    for (const string& ref : order) {
        cout << "[";
        for (size_t i = 0; i < sameWordGroup[ref].size(); i++) {
            cout << sameWordGroup[ref][i];
            if (i != sameWordGroup[ref].size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }
}

void merge(vector<char>& str, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<char> left(str.begin() + l, str.begin() + m + 1);
    vector<char> right(str.begin() + m + 1, str.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            str[k++] = left[i++];
        }
        else {
            str[k++] = right[j++];
        }
    }
    while (i < n1)
        str[k++] = left[i++];
    while (j < n2)
        str[k++] = right[j++];
}

void mergeSort(vector<char>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

string sorting(const string& str) {
    vector<char> characters(str.begin(), str.end());
    mergeSort(characters, 0, characters.size() - 1);
    string result;
    for (int i = 0;i < characters.size();i++) {
        result += characters[i];
    }
    return result;
}