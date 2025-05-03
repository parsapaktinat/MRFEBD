#include <bits/stdc++.h>
using namespace std;

int n,k,s,t;
vector<vector<int>> graph;
vector<bool> visited;
int countPath = 0;

void findPath(int,int);

int main()
{
    cin >> n >> k;

    int num;
    vector<int> temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> num;
            temp.push_back(num);
        }
        graph.push_back(temp);
        temp.clear();
    }

    cin >> s >> t;

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << graph[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0;i < n;i++) {
        visited.push_back(false);
    }
    visited[s] = true;
    findPath(s,1);
    cout << countPath << endl;

    return 0;
}

void findPath(int current, int visitedCount) {
    if (visitedCount == k) {
        if (current == t) {
            countPath++;
        }
        return;
    }

    for (int i = 0;i < n;i++) {
        if (graph[current][i] == 1 && !visited[i]) {
            visited[i] = true;
            findPath(i, visitedCount+1);
            visited[i] = false;
        }
    }
}