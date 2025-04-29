#include <bits/stdc++.h>

using namespace std;

void splitingWords(string colorAndTime,int& time,string& color);
bool isGold(const vector<int>& times, const vector<string>& colors, int& index ,int T, int K);
int isSilver(const vector<int>& times, int K);

int main() {
    int time,K,T;
    string color,colorO;

    vector<int> times;
    vector<string> colors;

    while (colorO != "end") {
        getline(cin,colorO);
        if (colorO != "end") {
            splitingWords(colorO,time,color);
            times.push_back(time);
            colors.push_back(color);
        }
    }

    cin >> K >> T;

    int index = 0;
    if (isGold(times,colors,index,T,K)) {
        cout << index+1;
    }
    else {
        cout << isSilver(times,K);
    }

    return 0;
}

void splitingWords(string colorAndTime,int& time,string& color) {
    string ref = " ";
    time = stoi(colorAndTime.substr(0,colorAndTime.find_first_of(ref)));
    color = colorAndTime.substr(colorAndTime.find_first_of(ref)+1);
}

bool isGold(const vector<int>& times, const vector<string>& colors, int& index ,int T, int K) {
    int sumOfTimes = 0;
    for (int i = 0;i < colors.size()-K+1;i++) {
        for (int j = 0;j < K;j++) {
            if (colors[i+j] == "Silver") {
                sumOfTimes = 0;
                break;
            }
            else {
                sumOfTimes += times[i+j];
            }
        }
        if (sumOfTimes == T) {
            index = i;
            return true;
        }
    }
    return false;
}

int isSilver(const vector<int>& times, int K) {
    int sumOfT = 0;
    vector<int> sumOfTimes;
    for (int i = 0;i < times.size()-K+1;i++) {
        for (int j = 0;j < K;j++) {
            sumOfT += times[i+j];
        }
        sumOfTimes.push_back(sumOfT);
        sumOfT = 0;
    }

    int minTime = sumOfTimes[0],index = 0;
    for (int i = 1;i < sumOfTimes.size();i++) {
        if (sumOfTimes[i] <= minTime) {
            index = i;
            minTime = sumOfTimes[i];
        }
    }
    return index+1;
}