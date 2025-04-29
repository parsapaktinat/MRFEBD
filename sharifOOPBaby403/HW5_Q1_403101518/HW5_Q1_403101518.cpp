#include <bits/stdc++.h>
using namespace std;

#define cs const string &

class FIFO{
private:
    int *queue; // Array for save data
    int size; // Maximum count of array
    int front;
    int rear;
    int count; // Number of elements now
public:
    FIFO(int size) : size(size), front(0), rear(-1), count(0) {
        queue = new int[size];
    }

    bool isFull() {
        return count == size;
    }

    bool isEmpty() {
        return count == 0;
    }

    void pushNumber(int value) {
        rear = (rear + 1) % size;
        queue[rear] = value;
        count++;
    }

    int popNum() {
        int value = queue[front];
        front = (front + 1) % size;
        count--;
        return value;
    }

    int printNumber(int index) {
        return queue[index];
    }

    void deleteing() {
        delete[] queue;
    }
};

class FIFOControl{
private:
	unordered_map<string, FIFO> fifos;
public:
	int createFIFO(cs name, cs n) {
		if (fifos.find(name) != fifos.end())
			return 1;
        FIFO newFifo(stoi(n));
		fifos.emplace(name,newFifo);
		return 2;
	}

    int pushNumber(int number, cs name) {
        if (fifos.find(name) == fifos.end())
            return 1;
        if (fifos.at(name).isFull())
            return 2;

        fifos.at(name).pushNumber(number);
        return 3;
    }

    int popNumber(cs name,int &v) {
        if (fifos.find(name) == fifos.end())
            return 1;
        if (fifos.at(name).isEmpty())
            return 2;
        v = fifos.at(name).popNum();
        return 3;
    }

    int deleteFifo(cs name) {
        if (fifos.find(name) == fifos.end())
            return 1;
        fifos.at(name).deleteing();
        fifos.erase(name);
        return 2;
    }

    int printFifoAtIndex(int index, cs name, int &value) {
        if (fifos.find(name) == fifos.end())
            return 1;
        value = fifos.at(name).printNumber(index);
        return 2;
    }

    void endProgram() {
        for (auto &fifo:fifos) {
            fifo.second.deleteing();
        }
    }
};

class View{
private:
    FIFOControl fifoControler;
public:
    void view() {
        string command,word;
        vector<string> cp;
       
		while (true) {
            getline(cin,command);
            stringstream ss(command);
            while (ss >> word)
                cp.push_back(word);

            if (cp[0] == "end") {
                cp.clear();
                fifoControler.endProgram();
                break;
            }

            else if (cp[0] == "create" && cp[1] == "FIFO" && cp.size() == 6) {
                string name = cp[2];
                string n = cp[5];
				int status = fifoControler.createFIFO(name,n);
				switch (status) {
					case 1:
						cout << "Error! this name is already exist." << endl;
						break;
					case 2:
						cout << "FIFO " << name << " created." << endl;
						break;
				}
            }

			else if (cp[0] == "push" && cp[2] == "to" && cp.size() == 5) {
                int number = stoi(cp[1]);
                string name = cp[4];
                int status = fifoControler.pushNumber(number,name);
                switch (status) {
                    case 1:
                        cout << "FIFO doesn't exist." << endl;
                        break;
                    case 2:
                        cout << "FIFO " << name << " is full." << endl;
                        break;
                    case 3:
                        cout << number << " added successfully!" << endl;
                        break;
                }
            }

            else if (cp[0] == "pop" && cp[1] == "from" && cp.size() == 4) {
                string name = cp[3];
                int value = 0;
                int status = fifoControler.popNumber(name,value);
                switch (status) {
                    case 1:
                        cout << "FIFO doesn't exist." << endl;
                        break;
                    case 2:
                        cout << "FIFO " << name << " is empty." << endl;
                        break;
                    case 3:
                        cout << value << endl;
                        break;
                }
            }

            else if (cp[0] == "delete" && cp[1] == "FIFO" && cp.size() == 3) {
                string name = cp[2];
                int status = fifoControler.deleteFifo(name);
                switch (status) {
                    case 1:
                        cout << "FIFO doesn't exist." << endl;
                        break;
                    case 2:
                        cout << "FIFO " << name << " deleted." << endl;
                        break;
                }
            }

            else if (cp[0] == "print" && cp[2] == "from" && cp[3] == "FIFO" && cp.size() == 5) {
                int index = stoi(cp[1]);
                string name = cp[4];
                int value = 0;
                int status = fifoControler.printFifoAtIndex(index,name,value);
                switch (status) {
                    case 1:
                        cout << "FIFO doesn't exist." << endl;
                        break;
                    case 2:
                        cout << value << endl;
                        break;
                }
            }

            cp.clear();
        }
    }
};

int main() {
    View v;
    v.view();
    return 0;
}
