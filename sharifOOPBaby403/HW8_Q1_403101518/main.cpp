#include <vector>
#include <string>
#include <exception>
#include <sstream>
#include <iostream>
using namespace std;

// *****************  Exceptions  *****************
class InvalidCommand : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid Command";
    }
};

class InvalidNameForPI : public exception {
public:
    const char* what() const noexcept override {
        return "!!! Error : Invalid name for PI !!!";
    }
};

// ***************** Helper Functions *****************
string trimString(const string& s) {
    size_t first = s.find_first_not_of(" \t");
    size_t last = s.find_last_not_of(" \t");
    return s.substr(first, last - first + 1);
}

// *****************  Models  *****************
class Response{
private:
    string text;
    bool hasError;
    string errorText;

public:
    bool errorHapen(bool e) const { return true; }

    void setErrorText(const string& et) {}

    void setText(const string& t) {}

    void print() {
        if (hasError)
            cout << errorText << endl;
        else
            cout << text << endl;
    }
};

class Data{
protected:
    string word;

public:
    virtual ~Data() = default;
    virtual void setWord(const string& w) = 0;

    string getWord() const { return word; }
};

class stringData : public Data{
public:
    void setWord(const string& w) override {
        word = w;
    }
};

class VectorData : public Data{
private:
    vector<int> vec;

public:
    vector<int> getVector() const { return vec; }

    void setWord(const string& w) override {
        word = w;
        for (char ch:word) {
            vec.push_back(static_cast<int>(ch));
        }
    }
};

// *****************  Controllers  *****************
class DataSet{
private:
    vector<Data*> datas;
    string name;

public:
    DataSet(const string& _name, const vector<Data*>& _datas) : name(_name), datas(_datas) {}
    DataSet() = default;

    ~DataSet() {
        for (auto data : datas) {
            delete data;
        }
    }

    vector<Data*> getAllData() const { return datas; }

    Data* getDataAt(int i) { return datas[i]; }

    void cinData() {}
};

class PIModel {
protected:
    string name;
    int version;
    DataSet trainData;

public:
    PIModel(const string& n, int v) : name(n), version(v) {}

    ~PIModel() = default;

    string getName() const { return name; }

    int getVersion() const { return version; }

    DataSet getDataSet() { return trainData; }

    void setYourNameAndVersion() {}

    virtual void train(DataSet &ds) = 0;

    virtual Response response(const string &input) = 0;
};

class Parrots : public PIModel{
public:
    Parrots(const string& n, int v) : PIModel(n, v) {}

    void train(DataSet& ds) override { trainData = ds; }

    Response response (const string& input) override {

    }
};

class Grammarly : public PIModel{
private:
    bool autoCorrect;

public:
    Grammarly(const string& n, int v) : PIModel(n, v) {}

    void setAutoCorrect(bool ac) {}

    void train(DataSet& ds) override { trainData = ds; }

    Response response (const string& input) override {

    }
};

class MathGeek : public PIModel{
private:
    int dataVectorSize;

public:
    MathGeek(const string& n, int v) : PIModel(n, v) {}

    void setDataVectorSize(int dvs) {}

    void train(DataSet& ds) override { trainData = ds; }

    Response response (const string& input) override {

    }
};

// *****************  View  *****************
class View{
private:
    vector<PIModel *> piModels;
    DataSet
    int parrotCounter = 0, grammarlyCounter = 0, mathGeekCounter = 0;

public:
    ~View () {
        for (PIModel* piModel : piModels)
            delete piModel;
    }

    void run() {
        vector<string> cp;
        string line,word;

        while (true) {
            getline(cin, line);
            stringstream ss(line);

            while (ss >> word)
                cp.push_back(word);

            try {
                if (cp[0] == "!create" && cp[1] == "PI" && cp[2] == ":" && cp.size() == 4) {
                    if (cp[3] == "Parrots") {
                        cout << "Parrots_v" << ++parrotCounter << " created" << endl;
                        piModels.push_back(new Parrots("Parrots_v", parrotCounter));
                    }

                    else if (cp[3] == "Grammarly") {
                        cout << "Grammarlt_v" << ++grammarlyCounter << " created" << endl;
                        piModels.push_back(new Grammarly("Grammarly_v", grammarlyCounter));
                    }

                    else if (cp[3] == "MathGeek") {

                        cout << "MathGeek_v" << ++mathGeekCounter << " created" << endl;
                        piModels.push_back(new MathGeek("MathGeek_v", mathGeekCounter));
                    }

                    else
                        throw InvalidNameForPI();
                }

                else if (cp[1] == "<-" && cp[2] == "$INTRO" && cp.size() == 3) {
                    string name = cp[0];
                    int version = name.back() - 48;
                    string nameWithoutVersion = name.substr(0,name.size() - 1);

                    bool piModelFound = false;
                    for (PIModel* piModel : piModels) {
                        if (piModel->getName() == nameWithoutVersion && piModel->getVersion() == version) {
                            cout << name << " -> Hi! I'm Parrots. You are using version " << version << "!" << endl;
                            piModelFound = true;
                            break;
                        }
                    }

                    if (!piModelFound)
                        throw InvalidCommand();
                }

                else if (cp[0] == "!create" && cp[2] == ":" && cp[3] == "word" && cp[4] == "count" && cp.size() == 7) {
                    int wordCount = stoi(cp[6]);
                    string dataSetName = cp[1];
                    vector<string> datas;
                    string l;
                    for (int i = 0;i < wordCount;i++) {
                        getline(cin,l);
                        string trimedL = trimString(l);
                        datas.push_back(l);
                        cout << "pushed word: \"" << l << "\"" << endl;
                    }
                }

                else
                    throw InvalidCommand();

                cp.clear();
            }
            catch (const exception& e) {
                cout << e.what() << endl;
                cp.clear();
            }
        }
    }
};

int main() {
    View view;
    view.run();
    return 0;
}