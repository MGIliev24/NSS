#include <iostream>
#include <string>
#include "test.h"
#include "gui.h"
#include "colors.h"
#include "randomizer.h"

using namespace std;

// Runs a 20-question test drawn from the question bank and updates the user's stats
void runItTest(Question questionBank[], StatisticsData& stats)
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("IT TEST  -  20 QUESTIONS");

    // Select 20 questions with category distribution: 7 HTML, 7 CSS, 6 JS
    int selectedIndexes[testQuestionCount];
    bool used[questionBankSize];
    for (int i = 0; i < questionBankSize; i++)
        used[i] = false;

    int cur = 0;
    int needs[3] = { 7, 7, 6 };
    int lo[3] = { 0, 10, 20 };
    int hi[3] = { 9, 19, 29 };

    for (int cat = 0; cat < 3; cat++)
    {
        while (needs[cat] > 0)
        {
            int idx = getRandomInt(lo[cat], hi[cat]);
            if (!used[idx])
            {
                used[idx] = true;
                selectedIndexes[cur++] = idx;
                needs[cat]--;
            }
        }
    }

    // Shuffle selected questions for variety
    for (int i = 0; i < testQuestionCount - 1; i++)
    {
        int j = getRandomInt(i, testQuestionCount - 1);
        int tmp = selectedIndexes[i];
        selectedIndexes[i] = selectedIndexes[j];
        selectedIndexes[j] = tmp;
    }

    int correct = 0;
    for (int i = 0; i < testQuestionCount; i++)
    {
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("IT TEST  -  20 QUESTIONS");
        
        Question& q = questionBank[selectedIndexes[i]];

        printSectionTitle("Question " + to_string(i + 1) + " of " + to_string(testQuestionCount));
        cout << "\n";
        printCenteredText(q.text);
        cout << "\n";

        if (q.category == 0) stats.htmlTotal++;
        else if (q.category == 1) stats.cssTotal++;
        else                      stats.jsTotal++;

        // Display answer choices via arrow-key menu
        string opts[3];
        opts[0] = "A)  " + q.optionA;
        opts[1] = "B)  " + q.optionB;
        opts[2] = "C)  " + q.optionC;
        int idx = arrowMenu(opts, 3);
        char answer = (char)('A' + idx);

        if (answer == q.correctAnswer)
        {
            cout << "\n" << getMintColor();
            printCenteredText("Correct!");
            cout << getResetColor();
            correct++;
            if (q.category == 0) stats.htmlCorrect++;
            else if (q.category == 1) stats.cssCorrect++;
            else                      stats.jsCorrect++;
        }
        else
        {
            cout << "\n" << getRoseColor();
            printCenteredText("Wrong!  Correct answer: " + string(1, q.correctAnswer));
            cout << getResetColor();
        }
        cout << "\n";
    }

    // Calculate grade on Bulgarian 2–6 scale
    double pct = (double)correct / testQuestionCount;
    double grade = 2.0;
    if (pct >= 0.90) grade = 6.0;
    else if (pct >= 0.75) grade = 5.0;
    else if (pct >= 0.60) grade = 4.0;
    else if (pct >= 0.45) grade = 3.0;

    string scoreStr = to_string(correct) + " / " + to_string(testQuestionCount)
        + "   (" + to_string((int)(pct * 100)) + "%)";

    clearScreen();
    printAsciiTitle();
    printCenteredTitle("IT TEST  -  20 QUESTIONS");
    
    printSectionTitle("TEST RESULT");
    printLabelValue("Score ", scoreStr);
    printLabelValue("Grade ", to_string((int)grade) + " / 6");
    cout << "\n";

    updateOverallStatistics(stats, grade);
    waitForEnter();
}