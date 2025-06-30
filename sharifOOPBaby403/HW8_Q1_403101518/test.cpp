#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <memory>
#include <map>
#include <limits>
using namespace std;

// Utility Functions
string trimStart(const string& s) {
    size_t start = s.find_first_not_of(' ');
    return (start == string::npos) ? "" : s.substr(start);
}

vector<int> stringToAsciiVector(const string& s) {
    vector<int> res;
    for (char c : s) res.push_back((int)c);
    return res;
}

int sumVector(const vector<int>& v) {
    int s = 0;
    for (int i : v) s += i;
    return s;
}

// Levenshtein distance
int compareStrings(const string& s1, const string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for(int i=0;i<=m;i++) dp[i][0]=i;
    for(int j=0;j<=n;j++) dp[0][j]=j;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1];
            else dp[i][j]=1+min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    return dp[m][n];
}

// ---------------- Response Class ----------------
class Response {
    string text;
    bool hasError;
    string errorText;
public:
    Response() : hasError(false) {}
    void errorHappen(bool e) { hasError = e; }
    void setErrorText(const string& et) { errorText = et; }
    void setText(const string& t) { text = t; }
    void print() {
        if (hasError) cout << errorText << endl;
        else cout << text << endl;
    }
};

// ---------------- Data Classes ----------------
class Data {
protected:
    string word;
public:
    virtual void setWord(string w) = 0;
    string getWord() { return word; }
    virtual vector<int> getVector() { return {}; }
};

class StringData : public Data {
public:
    void setWord(string w) override { word = w; }
};

class VectorData : public Data {
    vector<int> vec;
public:
    void setWord(string w) override {
        word = w;
        vec = stringToAsciiVector(w);
    }
    vector<int> getVector() override { return vec; }
};

// ---------------- DataSet Class ----------------
class DataSet {
    vector<shared_ptr<Data>> data;
public:
    string name;
    void cinData(bool isVector) {
        int cnt;
        cin >> cnt;
        cin.ignore();
        for (int i = 0; i < cnt; i++) {
            string line;
            getline(cin, line);
            shared_ptr<Data> d;
            if (isVector) d = make_shared<VectorData>();
            else d = make_shared<StringData>();
            d->setWord(trimStart(line));
            data.push_back(d);
        }
    }
    vector<shared_ptr<Data>> getDataAll() { return data; }
    shared_ptr<Data> getDataAt(int i) { return data.at(i); }
};

// ---------------- PI Model Classes ----------------
class PIModel {
protected:
    string name;
    int version;
    DataSet trainData;
public:
    PIModel(string n, int v) : name(n), version(v) {}
    virtual void train(DataSet ds) = 0;
    virtual Response response(string input) = 0;
    void sayYourNameAndVersion() {
        cout << "Hi! I'm " << name << ". You are using version " << version << "!" << endl;
    }
    void setTrainData(DataSet ds) { trainData = ds; }
    DataSet getDataSet() { return trainData; }
};

class Parrots : public PIModel {
public:
    Parrots(int v) : PIModel("Parrots", v) {}
    void train(DataSet ds) override { trainData = ds; }
    Response response(string input) override {
        Response r;
        string txt = trimStart(input);
        if (txt == "$INTRO") {
            r.setText("Hi! I'm Parrots. You are using version " + to_string(version) + "!");
        } else {
            r.setText(txt);
        }
        return r;
    }
};

class Grammarly : public PIModel {
    bool autocorrect = false;
public:
    Grammarly(int v) : PIModel("Grammarly", v) {}
    void train(DataSet ds) override { trainData = ds; }
    void setAutocorrect(bool ac) { autocorrect = ac; }
    Response response(string input) override {
        Response r;
        string txt = trimStart(input);
        if (txt == "$INTRO") {
            r.setText("Hi! I'm Grammarly. You are using version " + to_string(version) + "!");
        } else if (txt == "$ATON") {
            autocorrect = true;
            r.setText("autocorrect <= true");
        } else if (txt == "$ATOFF") {
            autocorrect = false;
            r.setText("autocorrect <= false");
        } else if (!autocorrect) {
            r.setText(txt);
        } else {
            int minDist = numeric_limits<int>::max();
            string closest;
            for (auto d : trainData.getDataAll()) {
                int dist = compareStrings(txt, d->getWord());
                if (dist < minDist) {
                    minDist = dist;
                    closest = d->getWord();
                }
            }
            r.setText(closest);
        }
        return r;
    }
};

class MathGeek : public PIModel {
    int DataVectorSize = 5;
public:
    MathGeek(int v) : PIModel("MathGeek", v) {}
    void train(DataSet ds) override {
        vector<shared_ptr<Data>> v = ds.getDataAll();
        for(auto& d : v) {
            auto vec = d->getVector();
            if(vec.size() > DataVectorSize)
                vec.erase(vec.begin(), vec.end() - DataVectorSize);
            while(vec.size() < DataVectorSize)
                vec.push_back(32);
        }
        trainData = ds;
    }
    Response response(string input) override {
        Response r;
        string txt = trimStart(input);
        if (txt == "$INTRO") {
            r.setText("Hi! I'm MathGeek. You are using version " + to_string(version) + "!");
        } else if (txt.substr(0,5) == "$DVS_") {
            string expr = txt.substr(5);
            try {
                int newSize = stoi(expr);
                DataVectorSize = newSize;
                r.setText("DataVectorSize <= " + to_string(newSize));
            } catch (...) {
                r.setErrorText("!!! Invalid DataVectorSize !!! My DataVectorSize = " + to_string(DataVectorSize));
                r.errorHappen(true);
            }
        } else {
            auto inputVec = stringToAsciiVector(txt);
            int inputSum = accumulate(inputVec.begin(), inputVec.end(),0);
            int minDiff = numeric_limits<int>::max();
            string closest;
            for(auto d : trainData.getDataAll()) {
                int s = sumVector(d->getVector());
                int diff = abs(s - inputSum);
                if(diff < minDiff) {
                    minDiff = diff;
                    closest = d->getWord();
                }
            }
            r.setText(closest);
        }
        return r;
    }
};

// ---------------- Main ----------------
int main() {
    // از اینجا می‌توانید دستورات را بخوانید و مدیریت کنید.
    cout << "Program Ready. Please implement command parsing logic as per your needs." << endl;
    return 0;
}
