#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define cs const string&

int streak = 0;
int numberOfCorrectAnswers = 0;
int numberOfIncorrectAnswers = 0;

int numberOfAllFlashcardsReviewed() {
    return numberOfCorrectAnswers + numberOfIncorrectAnswers;
}

class Flashcard {
private:
    string question;
    string answer;

public:
    Flashcard(cs _question, cs _answer) : question(_question), answer(_answer) {}
};

class Controller {
private:
    vector<Flashcard *> daily;
    vector<Flashcard *> weekly;
    vector<Flashcard *> monthly;

public:
    // Add flashcard
    void addFlashcard(cs question, cs answer) {
        daily.push_back(new Flashcard(question, answer));
    }
};

int main()
{
    Controller controller;
    string line, word;
    vector<string> cp;

    while (getline(cin, line)) {
        stringstream ss(line);
        while (ss >> word)
            cp.push_back(word);

        if (cp[0] == "streak") {
            cout << "Your current streak is: " << streak << endl;
        }

        else if (cp[0] == "add" && cp[1] == "flashcard") {
            string question, answer;
            getline(cin, question);
            getline(cin, answer);
            controller.addFlashcard(question, answer);
            cout << "flashcard added to the daily box" << endl;
        }

        else if (cp[0] == "review" && cp[1] == "today") {
            int numberOfFlashcards = stoi(cp[2]);
        }

        else if (cp[0] == "get" && cp[1] == "report" && cp.size() == 4) {
            string startDay = cp[2];
            string endDay = cp[3];
            if (startDay == endDay)
                cout << "Day: " << startDay << endl;
            else
                cout << "Day: " << startDay << " to " << endDay << endl;
            cout << "Correct Answers: " << numberOfCorrectAnswers << endl;
            cout << "Incorrect Answers: " << numberOfIncorrectAnswers << endl;
            cout << "Total: " << numberOfAllFlashcardsReviewed() << endl;
        }

        else if ()
    }

    return 0;
}
