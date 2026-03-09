#include <iostream>

using namespace std;

int main()
{
    Question questions[totalQuestions];
    initializeQuestions(questions);

    int choice;
    do
    {
        showMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int lessonChoice;
            showLessonMenu();
            cin >> lessonChoice;
            if (lessonChoice == 1) htmlLesson();
            if (lessonChoice == 2) cssLesson();
            if (lessonChoice == 3) jsLesson();
            break;
        }
        case 2:
        {
            int score = startTest(questions);
            showStatistics(score);
            break;
        }
        }

    } while (choice != 0);

    return 0;
}
