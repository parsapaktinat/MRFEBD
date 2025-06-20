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
// *****************  Exceptions  *****************


// *****************  Models  *****************
class Response{
private:
    string text;
    bool hasError;
    string errorText;

public:
    bool errorHapen(bool e) {}
    void setErrorText(const string& et) {}
    void setText(const string& t) {}
    void print() {}
};

class Data{
protected:
    string word;

public:
    virtual ~Data() = default;
    virtual void setWord(const string& w) = 0;
    string getWord() {}
};

class VectorData : public Data{
private:
    vector<int> vec;

public:
    vector<int> getVector() {}
    void setWord(const string& w) override {
        word = w;
        for (char ch:word) {
            vec.push_back(static_cast<int>(ch));
        }
    }
};

class stringData : public Data{
public:
    void setWord(const string& w) override {
        word = w;
    }
};
// *****************  Models  *****************


// *****************  Controllers  *****************
class DataSet{
private:
    vector<Data*> datas;
    string name;

public:
    vector<Data*> getAllData() {}
    Data* getDataAt(int i) {}

    void cinData() {}
};

class PIModel {
protected:
    string name;
    int version;
    DataSet trainDate;

public:
    PIModel(const string &n, int v) : name(n), version(v) {}

    DataSet getDataSet() {}

    void setYourNameAndVersion() {}

    virtual void train(DataSet &ds) = 0;

    virtual Response response(const string &input) = 0;
};

class Parrots : public PIModel{
public:
    Parrots(const string& n, int v) : PIModel(n, v) {}

    void train(DataSet& ds) override {
        trainDate = ds;
    }

    Response response (const string& input) override {

    }
};

class Grammarly : public PIModel{
private:
    bool autoCorrect;

public:
    Grammarly(const string& n, int v) : PIModel(n, v) {}

    void setAutoCorrect(bool ac) {}

    void train(DataSet& ds) override {
        trainDate = ds;
    }

    Response response (const string& input) override {

    }
};

class MathGeek : public PIModel{
private:
    int dataVectorSize;

public:
    MathGeek(const string& n, int v) : PIModel(n, v) {}

    void setDataVectorSize(int dvs) {}

    void train(DataSet& ds) override {
        trainDate = ds;
    }

    Response response (const string& input) override {

    }
};
// *****************  Controllers  *****************


// *****************  View  *****************
class View{
private:
    vector<PIModel *> piModels;
    int parrotCounter = 0, grammarlyCounter = 0, mathGeekCounter = 0;

public:
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
                        Parrots("Parrots_v", ++parrotCounter);
                        cout << "Parrots_v" << parrotCounter << " created" << endl;
                    }

                    else if (cp[3] == "Grammarly") {
                        Grammarly("Grammarly_v", ++grammarlyCounter);
                        cout << "Grammarlt_v" << grammarlyCounter << " created" << endl;
                    }

                    else if (cp[3] == "MathGeek") {
                        MathGeek("MathGeek_v", ++mathGeekCounter);
                        cout << "MathGeek_v" << mathGeekCounter << " created" << endl;
                    }

                    else
                        throw InvalidNameForPI();
                }

                else
                    throw InvalidCommand();
            }
            catch (const exception& e) {
                cout << e.what() << endl;
                cp.clear();
            }

            cp.clear();
        }
    }
};
// *****************  View  *****************


int main() {
    View view;
    view.run();
    return 0;
}