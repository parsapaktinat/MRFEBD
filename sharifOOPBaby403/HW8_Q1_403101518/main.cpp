#include <vector>
#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>
using namespace std;

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

string trimString(const string& s) {
    size_t first = s.find_first_not_of(" \t");
    size_t last = s.find_last_not_of(" \t");
    return s.substr(first, last - first + 1);
}

class Response{
private:
    string text;
    bool hasError;
    string errorText;

public:
    Response() { hasError = false; }

    bool errorHapen(bool e) const { return true; }
    void setErrorText(const string& et) { errorText= et; }
    void setText(const string& t) { text = t; }

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
    virtual ~Data() {}

    virtual void setWord(const string& w) = 0;
    virtual string getWord() const { return word; }
};

class StringData : public Data{
public:
    StringData(const string& line) { setWord(line); }

    void setWord(const string& w) override { word = w; }
};

class VectorData : public Data{
private:
    vector<int> vec;

public:
    VectorData(const string& line, int dataVectorSize) { 
        setWord(line); 
        vec.resize(dataVectorSize, 32);
    }

    vector<int> getVector() const { return vec; }
    void setWord(const string& w) override {
        word = w;
        for (char ch : word) {
            vec.push_back(static_cast<int>(ch));
        }
    }
};

class DataSet {
private:
    vector<unique_ptr<Data>> datas;
    string name;

public:
    DataSet(const string& name) : name(name) {}
    DataSet() = default;

    void addData(unique_ptr<Data> data) {
        datas.push_back(move(data));
    }

    void changeToVectorData(int dataVectorSize) {
        vector<unique_ptr<Data>> newDatas;
        
        for (const auto& data : datas) {
            string word = data->getWord();
            newDatas.push_back(make_unique<VectorData>(word, dataVectorSize));
        }
        
        datas.clear();

        datas = newDatas;
    }

    void changeToStringData() {
        vector<unique_ptr<Data>> newDatas;
        
        for (const auto& data : datas) {
            string word = data->getWord();
            newDatas.push_back(make_unique<StringData>(word));
        }
        
        datas.clear();

        datas = newDatas;
    }

    const vector<unique_ptr<Data>>& getAllData() const { return datas; }
    Data* getDataAt(size_t i) { return datas[i].get(); }
    
    void cinData(int wordCount, const string& dataSetName) {
        cout << "lets push " << wordCount << " words to " << dataSetName << " !" << endl;
        string l;
        for (int i = 0; i < wordCount; i++) {
            getline(cin, l);
            string trimedL = trimString(l);
            datas.push_back(make_unique<StringData>(trimedL));
            cout << "pushed word: \"" << trimedL << "\"" << endl;
        }
    }
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
    virtual void train(const DataSet &ds) = 0;
    virtual Response response(const string &input) = 0;
};

class Parrots : public PIModel{
public:
    Parrots(const string& n, int v) : PIModel(n, v) {}

    void train(DataSet& ds) override { 
        cout << "Hello -------------- 6" << endl;
        ds.changeToStringData();
        cout << "Hello -------------- 4" << endl;
        trainData = DataSet();
        for (const auto& data : ds.getAllData()) {
            trainData.getAllData().push_back(make_unique<StringData>(data->getWord()));
        }
        cout << "Hello -------------- 5" << endl;
    }

    Response response (const string& input) override {
        Response result;
        result.setText(input);
        return result;
    }
};

class Grammarly : public PIModel{
private:
    bool autoCorrect;

public:
    Grammarly(const string& n, int v) : PIModel(n, v) {}

    void setAutoCorrect(bool ac) {}

    void train(DataSet& ds) override { 
        ds.changeToStringData();
        trainData = ds; 
    }

    Response response (const string& input) override {}
};

class MathGeek : public PIModel{
private:
    int dataVectorSize;

public:
    MathGeek(const string& n, int v) : PIModel(n, v) { dataVectorSize = 5; }

    void setDataVectorSize(int dvs) {}

    void train(DataSet& ds) override { 
        ds.changeToVectorData(dataVectorSize);
    }

    Response response (const string& input) override {}
};

class Controller{
private:
    map<string, unique_ptr<PIModel>> piModels; // name_version -> PI
    map<string, DataSet> dataSets;  // name -> DataSet
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
                        cout << "Parrots_v" << ++parrotCounter << " created" << endl;
                        string name = "Parrots_v";
                        name.append(to_string(parrotCounter));
                        piModels.emplace(name ,new Parrots("Parrots_v", parrotCounter));
                    } else if (cp[3] == "Grammarly") {
                        cout << "Grammarly_v" << ++grammarlyCounter << " created" << endl;
                        string name = "Grammarlt_v";
                        name.append(to_string(grammarlyCounter));
                        piModels.emplace(name, new Grammarly("Grammarly_v", grammarlyCounter));
                    } else if (cp[3] == "MathGeek") {
                        cout << "MathGeek_v" << ++mathGeekCounter << " created" << endl;
                        string name = "MathGeek_v";
                        name.append(to_string(mathGeekCounter));
                        piModels.emplace(name, new MathGeek("MathGeek_v", mathGeekCounter));
                    } else
                        throw InvalidNameForPI();
                }

                else if (cp[1] == "<-" && cp[2] == "$INTRO" && cp.size() == 3) {
                    string name = cp[0];
                    int version = name.back() - 48;
                    string nameWithoutVersion = name.substr(0,name.size() - 1);
                    bool piModelFound = false;
                    for (auto& piModel : piModels) {
                        if (piModel.second->getName() == nameWithoutVersion && piModel.second->getVersion() == version) {
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
                    DataSet dataSet(dataSetName);
                    dataSet.cinData(wordCount, dataSetName);
                    dataSets.emplace(dataSetName, dataSet);
                }

                else if (cp[0] == "!train" && cp[2] == "with" && cp.size() == 4) {
                    string PIfullName = cp[1];
                    string PIname = PIfullName.substr(0, PIfullName.size() - 1);
                    cout << "Hello -------------- 1" << endl;
                    string dataSetName = cp[3];
                    int counter = static_cast<char>(PIfullName.back()) - 48;
                    cout << "Hello -------------- 2" << endl;
                    piModels[PIfullName]->train(dataSets[dataSetName]);
                    cout << "Hello -------------- 3" << endl;
                }

                else if (cp[1] == "<-" && cp.size() >= 3) {
                    string name = cp[0];
                    // int version = name.back() - 48;
                    // string nameWithoutVersion = name.substr(0,name.size() - 1);

                    size_t t = line.find_first_of(" ", line.find_first_of(" ") + 1);
                    string input = line.substr(t);

                    Response res = piModels[name]->response(input);
                    cout << name << " -> ";
                    res.print();
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
    Controller controller;
    controller.run();
    return 0;
}