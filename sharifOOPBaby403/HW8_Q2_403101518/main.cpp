#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

#define cs const string&

class Flashcard {
private:
    string question;
    string answer;

public:
    Flashcard(cs _question, cs _answer) : question(_question), answer(_answer) {}

    string getQuestion() const {
        return question;
    }

    string getAnswer() const {
        return answer;
    }
};

struct Day {
    int correctAnswer;
    int incorrectAnswer;

    int getTotal() { return correctAnswer + incorrectAnswer; }
};

class Controller {
private:
    vector<Flashcard *> daily;
    vector<Flashcard *> weekly;
    vector<Flashcard *> monthly;
    int currentDay;
    int streak;
    int totalParticipationDays;
    int numberOfMasterFlashcards;
    int numberOfCorrectAnswers;
    int numberOfIncorrectAnswers;

public:
    // Constructor
    Controller() {
        currentDay = 1;
        streak = 0;
        totalParticipationDays = 0;
        numberOfMasterFlashcards = 0;
        numberOfCorrectAnswers = 0;
        numberOfIncorrectAnswers = 0;
    }

    // Getter and setters
    int getCurrentDay() const {
        return currentDay;
    }

    int getStreak() const {
        return streak;
    }

    int getTotalParticipationDays() const {
        return totalParticipationDays;
    }

    int getNumberOfMasterFlashcards() const {
        return numberOfMasterFlashcards;
    }

    int getNumberOfCorrectAnswers() const {
        return numberOfCorrectAnswers;
    }

    int getNumberOfIncorrectAnswers() const {
        return numberOfIncorrectAnswers;
    }

    // Add flashcard
    void addFlashcard(cs question, cs answer) {
        daily.push_back(new Flashcard(question, answer));
    }

    // Next day
    void nextDay() {
        currentDay++;
    }

    // Helper function
    int numberOfAllFlashcardsReviewed() {
        return numberOfCorrectAnswers + numberOfIncorrectAnswers;
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
            cout << "Your current streak is: " << controller.getStreak() << endl;
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
            cout << "Correct Answers: " << controller.getNumberOfCorrectAnswers() << endl;
            cout << "Incorrect Answers: " << controller.getNumberOfIncorrectAnswers() << endl;
            cout << "Total: " << controller.numberOfAllFlashcardsReviewed() << endl;
        }

        else if (cp[0] == "get" && cp[1] == "progress" && cp[3] == "report") {
            cout << "Challenge Progress Report:" << endl;
            cout << "Day of the Challenge: " << controller.getCurrentDay() << endl;
            cout << "Streak: " << controller.getStreak() << endl;
            cout << "Total Days Participated: " << controller.getTotalParticipationDays() << endl;
            cout << "Mastered Flashcards: " << controller.getNumberOfMasterFlashcards() << endl;
        }

        else if (cp[0] == "next" && cp[1] == "day") {
            cout << "--------------------------------------------------" << endl;
            controller.nextDay();
            cout << "It is day " << controller.getCurrentDay() << " of your journey." << endl;
            cout << "Your current streak is: " << controller.getStreak() << endl;
        }
    }

    return 0;
}
