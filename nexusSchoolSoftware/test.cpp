#include <iostream>
#include "test.h"
#include "gui.h"
#include "colors.h"
#include "randomizer.h"

using namespace std;

static char readAnswer()
{
    char answer;
    while (true)
    {
        cout << "Your answer (A, B, C): ";
        cin >> answer;

        if (answer >= 'a' && answer <= 'z')
        {
            answer = (char)(answer - ('a' - 'A'));
        }

        if (answer == 'A' || answer == 'B' || answer == 'C')
        {
            return answer;
        }

        cout << "Invalid answer. Please enter A, B or C.\n";
    }
}

void runItTest(Question questionBank[], StatisticsData& stats)
{
    clearScreen();
    printCenteredTitle("NEXUS IT TEST - 20 QUESTIONS");

    int selectedIndexes[testQuestionCount];
    bool used[questionBankSize];
    for (int i = 0; i < questionBankSize; i++)
    {
        used[i] = false;
    }

    int currentIndex = 0;
    int htmlNeeded = 7;
    int cssNeeded = 7;
    int jsNeeded = 6;

    while (htmlNeeded > 0)
    {
        int index = getRandomInt(0, 9);
        if (!used[index])
        {
            used[index] = true;
            selectedIndexes[currentIndex++] = index;
            htmlNeeded--;
        }
    }

    while (cssNeeded > 0)
    {
        int index = getRandomInt(10, 19);
        if (!used[index])
        {
            used[index] = true;
            selectedIndexes[currentIndex++] = index;
            cssNeeded--;
        }
    }

    while (jsNeeded > 0)
    {
        int index = getRandomInt(20, 29);
        if (!used[index])
        {
            used[index] = true;
            selectedIndexes[currentIndex++] = index;
            jsNeeded--;
        }
    }

    for (int i = 0; i < testQuestionCount - 1; i++)
    {
        int j = getRandomInt(i, testQuestionCount - 1);
        int temp = selectedIndexes[i];
        selectedIndexes[i] = selectedIndexes[j];
        selectedIndexes[j] = temp;
    }

    int correctAnswers = 0;

    for (int i = 0; i < testQuestionCount; i++)
    {
        int index = selectedIndexes[i];
        Question q = questionBank[index];

        cout << "\nQuestion " << (i + 1) << " of " << testQuestionCount << ":\n";
        printThinLine();
        cout << q.text << "\n";
        cout << " A) " << q.optionA << "\n";
        cout << " B) " << q.optionB << "\n";
        cout << " C) " << q.optionC << "\n";

        char answer = readAnswer();

        if (q.category == 0)
        {
            stats.htmlTotal++;
        }
        else if (q.category == 1)
        {
            stats.cssTotal++;
        }
        else if (q.category == 2)
        {
            stats.jsTotal++;
        }

        if (answer == q.correctAnswer)
        {
            cout << "Correct!\n";
            correctAnswers++;

            if (q.category == 0)
            {
                stats.htmlCorrect++;
            }
            else if (q.category == 1)
            {
                stats.cssCorrect++;
            }
            else if (q.category == 2)
            {
                stats.jsCorrect++;
            }
        }
        else
        {
            cout << "Wrong. Correct answer is " << q.correctAnswer << ".\n";
        }
    }

    double percent = (double)correctAnswers / (double)testQuestionCount;
    double grade = 2.0;

    if (percent >= 0.90)
    {
        grade = 6.0;
    }
    else if (percent >= 0.75)
    {
        grade = 5.0;
    }
    else if (percent >= 0.60)
    {
        grade = 4.0;
    }
    else if (percent >= 0.45)
    {
        grade = 3.0;
    }

    printSectionTitle("TEST RESULT");
    cout << "Correct answers : " << correctAnswers << " / " << testQuestionCount << "\n";
    cout << "Score percent   : " << percent * 100.0 << "%\n";
    cout << "Final grade     : " << grade << "\n";

    updateOverallStatistics(stats, grade);
    waitForEnter();
}

