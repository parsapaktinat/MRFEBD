#include <bits/stdc++.h>
using namespace std;

class Operator{
public:
    string addStrings(const string &num1, const string &num2) {
        string result;

        int carry = 0,sum;
        int i = num1.size() - 1, j = num2.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int digit1 = (i >= 0) ? num1[i] - '0' : 0;
            int digit2 = (j >= 0) ? num2[j] - '0' : 0;
            sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result += (sum % 10) + '0';
            i--;
            j--;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    bool isSmaller(const string &num1, const string &num2) {
        if (num1.size() != num2.size())
            return num1.size() < num2.size();
        return num1 < num2;
    }

    string subtractStrings(string &num1, string &num2) {
        bool negative = false;

        if (isSmaller(num1, num2)) {
            swap(num1, num2);
            negative = true;
        }

        string result;
        int i = num1.size() - 1, j = num2.size() - 1, borrow = 0;

        while (i >= 0) {
            int digit1 = num1[i] - '0';
            int digit2 = (j >= 0) ? num2[j] - '0' : 0;
            int diff = digit1 - digit2 - borrow;

            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            else
                borrow = 0;

            result += diff + '0';
            i--;
            j--;
        }

        while (result.size() > 1 && result.back() == '0')
            result.pop_back();

        reverse(result.begin(), result.end());

        if (negative)
            result = '-' + result;

        return result;
    }
};

class View{
private:
    Operator oper;
    string num1,num2;
    char op;
public:
    void view() {
        cin >> num1 >> num2 >> op;

        string num3,num1temp,num2temp,num3temp;

        if (op == '+') {
            if (num1[0] == '-' && num2[0] == '-') {
                num1temp = num1.erase(0,1);
                num2temp = num2.erase(0,1);
                num3temp = oper.addStrings(num1temp,num2temp);
                num3 = "-" + num3temp;
            }
            else if (num1[0] != '-' && num2[0] == '-') {
                num2temp = num2.erase(0,1);
                num3temp = oper.subtractStrings(num1,num2temp);
                num3 = num3temp;
            }
            else if (num1[0] == '-' && num2[0] != '-') {
                num1temp = num1.erase(0,1);
                num3temp = oper.subtractStrings(num2,num1temp);
                num3 = num3temp;
            }
            else if (num1[0] != '-' && num2[0] != '-') {
                num3 = oper.addStrings(num1,num2);
            }
        }
        else if (op == '-') {
            if (num1[0] == '-' && num2[0] == '-') {
                num1temp = num1.erase(0,1);
                num2temp = num2.erase(0,1);
                num3temp = oper.subtractStrings(num2temp,num1temp);
                num3 = num3temp;
            }
            else if (num1[0] != '-' && num2[0] == '-') {
                num2temp = num2.erase(0,1);
                num3temp = oper.addStrings(num1,num2temp);
                num3 = num3temp;
            }
            else if (num1[0] == '-' && num2[0] != '-') {
                num1temp = num1.erase(0,1);
                num3temp = oper.addStrings(num2,num1temp);
                num3 = "-" + num3temp;
            }
            else if (num1[0] != '-' && num2[0] != '-') {
                num3 = oper.subtractStrings(num1,num2);
            }
        }
        cout << num3;
    }
};

int main() {
    View view;
    view.view();
    return 0;
}