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

class LeitnerBox {
private:
    vector<Flashcard> flashcards;

public:
    void addFlashcard(const Flashcard& flashcard) {
        flashcards.push_back(flashcard);
    }

    vector<Flashcard> getForReview(int& count) {
        vector<Flashcard> result;
        if (count > flashcards.size()) {
            for (auto & flashcard : flashcards) {
                result.push_back(flashcard);
            }
            count -= flashcards.size();
        }

        else {
            for (auto it = flashcards.begin(); it != flashcards.end(); it++) {
                result.push_back(*it);
            }
        }

        return result;
    }
};

class Day {
private:

};

class Controller {
private:
    LeitnerBox daily, weekly, monthly;
    vector<Flashcard> masteredFlashCards;
    vector<int> daysPracticed;
    int lastDayPracticed;
    int currentDay;
    int streak;
    int totalParticipationDays;
    int numberOfMasterFlashcards;
    int numberOfCorrectAnswers;

public:
    // Constructor
    Controller() {
        currentDay = 1;
        streak = 0;
        totalParticipationDays = 0;
        numberOfMasterFlashcards = 0;
        numberOfCorrectAnswers = 0;
        lastDayPracticed = 0;
    }

    // Add flashcard
    void addFlashcard(cs question, cs answer) {
        daily.addFlashcard(Flashcard(question, answer));
    }

    // Review process
    void reviewToday(int numFlash) {
        vector<Flashcard> flashcards;
        flash
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

        if (cp[0] == "add" && cp[1] == "flashcard") {
            string question, answer;
            getline(cin, question);
            getline(cin, answer);
            controller.addFlashcard(question, answer);
            cout << "flashcard added to the daily box" << endl;
        }

        else if (cp[0] == "review" && cp[1] == "today") {
            int numberOfFlashcards = stoi(cp[2]);
            controller.reviewToday(numberOfFlashcards);
        }



        // else if (cp[0] == "get" && cp[1] == "report" && cp.size() == 4) {
        //     string startDay = cp[2];
        //     string endDay = cp[3];
        //     if (startDay == endDay)
        //         cout << "Day: " << startDay << endl;
        //     else
        //         cout << "Day: " << startDay << " to " << endDay << endl;
        //     cout << "Correct Answers: " << controller.getNumberOfCorrectAnswers() << endl;
        //     cout << "Incorrect Answers: " << controller.getNumberOfIncorrectAnswers() << endl;
        //     cout << "Total: " << controller.numberOfAllFlashcardsReviewed() << endl;
        // }
        //
        // else if (cp[0] == "get" && cp[1] == "progress" && cp[3] == "report") {
        //     cout << "Challenge Progress Report:" << endl;
        //     cout << "Day of the Challenge: " << controller.getCurrentDay() << endl;
        //     cout << "Streak: " << controller.getStreak() << endl;
        //     cout << "Total Days Participated: " << controller.getTotalParticipationDays() << endl;
        //     cout << "Mastered Flashcards: " << controller.getNumberOfMasterFlashcards() << endl;
        // }
        //
        // else if (cp[0] == "next" && cp[1] == "day") {
        //     cout << "--------------------------------------------------" << endl;
        //     controller.nextDay();
        //     cout << "It is day " << controller.getCurrentDay() << " of your journey." << endl;
        //     cout << "Your current streak is: " << controller.getStreak() << endl;
        // }
    }

    return 0;
}
