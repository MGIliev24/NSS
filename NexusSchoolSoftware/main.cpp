#include <iostream>
#include "headers/user.h"
#include "headers/lesson.h"
#include "headers/quizEngine.h"

using namespace std;

int main() {
    User u;
    SchoolModule sm;
    QuizEngine qe;

    if (!u.login()) return 0;

    int choice = 0;
    while (choice != 4) {
        cout << "\n1. Lessons\n2. Quiz\n3. Stats\n4. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            for (int i = 0; i < 3; i++) cout << i << ": " << sm.lessons[i].title << endl;
            int idx; cin >> idx;
            sm.displayLesson(idx);
        }
        else if (choice == 2) qe.runTest();
        else if (choice == 3) qe.showStatistics();
    }
    return 0;
}