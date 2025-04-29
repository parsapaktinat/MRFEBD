#include <bits/stdc++.h>
using namespace std;

bool invalidFounder(string& s);
void convertBinary(const string& hexNum, char *p);
void convertBiggestEndian(string& hexNum);
void convertLittleEndian(string& hexNum);

int main() {
    string hexNum;
    cin >> hexNum;

    if (hexNum.size() > 16) {
        cout << "Hexadecimal number exceeds 64-bit limit (16 hex digits)";
        return 0;
    }
    if (!invalidFounder(hexNum)) {
        cout << "Invalid hexadecimal digit";
        return 0;
    }

    char *p = new char[4*hexNum.size()];

    convertBinary(hexNum,p);
    for (int i = 0;i < 4*hexNum.size();i++) {
        cout << p[i];
    }
    cout << endl;

    // char *q = new char[4*hexNum.size()],*o = new char[4*hexNum.size()];
    // q = p;
    // o = p;
    char *q = p,*o = p;

    string hexNum2 = hexNum,hexNum3 = hexNum;
    convertBiggestEndian(hexNum2);
    convertBinary(hexNum2,q);
    for (int i = 0;i < 4*hexNum.size();i++) {
        cout << q[i];
    }
    cout << endl;

    convertLittleEndian(hexNum3);
    convertBinary(hexNum3,o);
    for (int i = 0;i < 4*hexNum.size();i++) {
        cout << o[i];
    }

    return 0;
}

bool invalidFounder(string& str) {
    for (char ch:str) {
        ch = tolower(ch);
        if (!isalnum(ch)) {
            return false;
        }
    }
    return true;
}

void convertBinary(const string& hexNum, char *p) {
    int index = 0;
    for (char ch:hexNum) {
        ch = tolower(ch);
        switch (ch) {
            case '0':
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '0';
                break;
            case '1':
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '1';
                break;
            case '2':
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '0';
                break;
            case '3':
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '1';
                break;
            case '4':
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '0';
                break;
            case '5':
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '1';
                break;
            case '6':
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '0';
                break;
            case '7':
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '1';
                break;
            case '8':
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '0';
                break;
            case '9':
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '0';
                p[index++] = '1';
                break;
            case 'a':
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '0';
                break;
            case 'b':
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '1';
                p[index++] = '1';
                break;
            case 'c':
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '0';
                break;
            case 'd':
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '0';
                p[index++] = '1';
                break;
            case 'e':
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '0';
                break;
            case 'f':
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '1';
                p[index++] = '1';
                break;
        }
    }
}

void convertBiggestEndian(string& hexNum) {
    for (int i = 0;i < hexNum.size();i+=2){
        for (int j = i;j < hexNum.size();j+=2) {
            if (hexNum[i] > hexNum[j]) {
                char temp = hexNum[i];
                hexNum[i] = hexNum[j];
                hexNum[j] = temp;
                temp = hexNum[i+1];
                hexNum[i+1] = hexNum[j+1];
                hexNum[j+1] = temp;
            }
        }
    }
}

void convertLittleEndian(string& hexNum) {
    for (int i = 0;i < hexNum.size();i+=2){
        for (int j = i;j < hexNum.size();j+=2) {
            if (hexNum[i] < hexNum[j]) {
                char temp = hexNum[i];
                hexNum[i] = hexNum[j];
                hexNum[j] = temp;
                temp = hexNum[i+1];
                hexNum[i+1] = hexNum[j+1];
                hexNum[j+1] = temp;
            }
        }
    }
}