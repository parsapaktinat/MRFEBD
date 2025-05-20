#include <bits/stdc++.h>
using namespace std;

// ------------- Exception example ------------------
class NameException : public exception {
public:
    const char* what() const noexcept override {
        return "Error: error output";
    }
};

// ------------- your code goes here ----------------


bool inputHandler(string line) {
    regex addDoctorPattern(R"(add doctor (\S+)\s*)");

    smatch matches;
    string cmd;

    if (regex_match(cmd, matches, addDoctorPattern)) {

    }
}

// ------ do not change main() function ------
int main() {
    string line;
    bool cond = true;
    while (cond) {
        getline(cin, line);
        try {
            cond = inputHandler(line);
        }
        catch (const exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}