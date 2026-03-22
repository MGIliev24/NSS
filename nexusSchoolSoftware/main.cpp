#include <iostream>
#include <string>
#include "colors.h"
#include "gui.h"
#include "question.h"
#include "test.h"
#include "statistics.h"
#include "randomizer.h"
#include "auth.h"
using namespace std;

int main()
{
    UserAccount accounts[maxAccounts];
    initializeAccounts(accounts, maxAccounts);
    string loggedInUser;

    if (!handleAuthentication(accounts, maxAccounts, loggedInUser))
    {
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("GOODBYE");
        printCenteredText("Exiting Nexus School Software.  See you next time!");
        cout << "\n";
        return 0;
    }

    // student ID — centeredInput keeps it visually centered, no raw cin
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("STUDENT ID");
    string idStr = centeredInput("Enter your numeric student ID: ");

    // parse digits manually — no stoul, no extra headers
    unsigned int studentId = 0;
    for (int i = 0; i < (int)idStr.length(); i++)
        if (idStr[i] >= '0' && idStr[i] <= '9')
            studentId = studentId * 10 + (unsigned int)(idStr[i] - '0');
    if (studentId == 0) studentId = 1;
    setSeed(studentId);

    Question questionBank[questionBankSize];
    initializeQuestionBank(questionBank, questionBankSize);
    StatisticsData statisticsData;
    initializeStatistics(statisticsData);

    // 0=Lessons, 1=Test, 2=Stats, 3=Exit
    int mainChoice = -1;
    while (mainChoice != 3)
    {
        mainChoice = showMainMenu();

        if (mainChoice == 0)
        {
            int lessonChoice = -1;
            while (lessonChoice != 3)
            {
                lessonChoice = showLessonsMenu();
                if (lessonChoice == 0) showHtmlLesson();
                else if (lessonChoice == 1) showCssLesson();
                else if (lessonChoice == 2) showJsLesson();
            }
        }
        else if (mainChoice == 1) runItTest(questionBank, statisticsData);
        else if (mainChoice == 2) showStatistics(statisticsData);
    }

    clearScreen();
    printAsciiTitle();
    printCenteredTitle("SESSION CLOSED");
    printCenteredText("Thanks for using Nexus School Software,  " + loggedInUser + "!");
    cout << "\n";
    return 0;
}
