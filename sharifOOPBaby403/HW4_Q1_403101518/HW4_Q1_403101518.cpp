#include <bits/stdc++.h>
using namespace std;

class HugeInt{
private:
    string number;
    string type;
    string name;
public:
    HugeInt(string number, string type, string name) : number(number), type(type), name(name) {}
    string getNum() {return number;}
    void setNum(const string& newNum) {number = newNum;}
    string getType() {return type;}
    void setType(const string &t) {type = t;}
    string getName() {return name;}
};

class Operator{
private:
    unordered_map<string,HugeInt> hugeInts;
public:
    bool createNumber(string name, string type, string number) {
        HugeInt num(number,type,name);
        hugeInts.emplace(name,num);
        return true;
    }

    bool sumTheNumbers(const string &name1, const string &name2, string &name3, string &type, string &number) {
        string num1,num2;
        if (hugeInts.find(name1) == hugeInts.end() || hugeInts.find(name2) == hugeInts.end())
            return false;
        if (hugeInts.at(name1).getType() != hugeInts.at(name2).getType())
            return false;

        num1 = hugeInts.at(name1).getNum();
        num2 = hugeInts.at(name2).getNum();
        type = hugeInts.at(name1).getType();

        number = addStrings(num1,num2,type);

        if (hugeInts.find(name3) != hugeInts.end()){
            hugeInts.at(name3).setNum(number);
            hugeInts.at(name3).setType(type);
        }
        else {
            HugeInt h(number,type,name3);
            hugeInts.emplace(name3,h);
        }
        return true;
    }

    string addStrings(const string &a, const string &b, const string &type) {
        string result;

        if (type == "Binary") {
            int carry = 0,sum;
            int i = a.size() - 1, j = b.size() - 1;

            while (i >= 0 || j >= 0 || carry) {
                int digit1 = (i >= 0) ? a[i] - '0' : 0;
                int digit2 = (j >= 0) ? b[j] - '0' : 0;
                sum = digit1 + digit2 + carry;
                carry = sum / 2;
                result += (sum % 2) + '0';
                i--; j--;
            }
        }

        else if (type == "Decimal") {
            int carry = 0,sum;
            int i = a.size() - 1, j = b.size() - 1;

            while (i >= 0 || j >= 0 || carry) {
                int digit1 = (i >= 0) ? a[i] - '0' : 0;
                int digit2 = (j >= 0) ? b[j] - '0' : 0;
                sum = digit1 + digit2 + carry;
                carry = sum / 10;
                result += (sum % 10) + '0';
                i--; j--;
            }
        }

        else if (type == "Hexadecimal") {
            int carry = 0,sum;
            int i = a.size() - 1, j = b.size() - 1;

            while (i >= 0 || j >= 0 || carry) {
                int digit1 = (i >= 0) ? (isdigit(a[i]) ? a[i] - '0' : a[i] - 'A' + 10) : 0;
                int digit2 = (j >= 0) ? (isdigit(b[j]) ? b[j] - '0' : b[j] - 'A' + 10) : 0;
                sum = digit1 + digit2 + carry;
                carry = sum / 16;
                int remainder = sum % 16;
                result += (remainder < 10) ? remainder + '0' : remainder - 10 + 'A';
                i--; j--;
            }
        }

        reverse(result.begin(), result.end());
        return result;
    }

    bool multiplyTheNumbers(const string &name1, const string &name2, string &name3, string &type, string &number) {
        string num1,num2;

        if (hugeInts.find(name1) == hugeInts.end() || hugeInts.find(name2) == hugeInts.end())
            return false;
        if (hugeInts.at(name1).getType() != hugeInts.at(name2).getType())
            return false;

        num1 = hugeInts.at(name1).getNum();
        num2 = hugeInts.at(name2).getNum();
        type = hugeInts.at(name1).getType();

        int base;
        if (type == "Decimal")
            base = 10;
        else if (type == "Binary")
            base = 2;
        else if (type == "Hexadecimal")
            base = 16;

        number = multiplyStrings(num1,num2,base);

        if (hugeInts.find(name3) != hugeInts.end()){
            hugeInts.at(name3).setNum(number);
            hugeInts.at(name3).setType(type);
        }
        else {
            HugeInt h(number,type,name3);
            hugeInts.emplace(name3,h);
        }
        return true;
    }

    string multiplyStrings(const string &num1, const string &num2, int base) {
        int len1 = num1.size(), len2 = num2.size();
        vector<int> result(len1 + len2, 0);

        for (int i = len1 - 1; i >= 0; i--) {
            int digit1 = (isdigit(num1[i]) ? num1[i] - '0' : num1[i] - 'A' + 10);
            for (int j = len2 - 1; j >= 0; j--) {
                int digit2 = (isdigit(num2[j]) ? num2[j] - '0' : num2[j] - 'A' + 10);
                int sum = digit1 * digit2 + result[i + j + 1];
                result[i + j + 1] = sum % base;
                result[i + j] += sum / base;
            }
        }

        std::string product;
        for (int num : result) {
            if (!(product.empty() && num == 0))
                product += (num < 10) ? num + '0' : num - 10 + 'A';
        }

        return product.empty() ? "0" : product;
    }
};

class View{
private:
    Operator oper;
public:
    void view() {
        string commandLine,word;
        vector<string> cp;

        while (true) {
            getline(cin,commandLine);
            stringstream ss(commandLine);

            while (ss >> word) {
                cp.push_back(word);
            }

            if (cp[0] == "end") {
                break;
            }

            else if (cp[0] == "create" && cp[2] == "as") {
                string name = cp[1], type = cp[3], number = cp[4];
                if (oper.createNumber(name,type,number)){
                    cout << name << " as " << type << " is " << number << endl;
                }
            }

            else if (cp[1] == "+" && cp[3] == "in") {
                string name1 = cp[0], name2 = cp[2], name3 = cp[4];
                string type,number;
                if (oper.sumTheNumbers(name1,name2,name3,type,number)){
                    cout << name3 << " as " << type << " is " << number << endl;
                }
            }

            else if (cp[1] == "*" && cp[3] == "in") {
                string name1 = cp[0], name2 = cp[2], name3 = cp[4];
                string type,number;
                if (oper.multiplyTheNumbers(name1,name2,name3,type,number)){
                    cout << name3 << " as " << type << " is " << number << endl;
                }
            }

            cp.clear();
            cout << endl;
        }
    }
};

int main() {
    View view;
    view.view();
    return 0;
}