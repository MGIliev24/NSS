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

static int readMenuChoice(int minValue, int maxValue)
{
    int choice;
    while (true)
    {
        cout << "Enter choice (" << minValue << "-" << maxValue << "): ";
        if (cin >> choice)
        {
            if (choice >= minValue && choice <= maxValue)
            {
                return choice;
            }
        }
        cin.clear();
        string dump;
        getline(cin >> ws, dump);
        cout << "Invalid input. Try again.\n";
    }
}

int main()
{
    clearScreen();
    printAsciiTitle();

    UserAccount accounts[maxAccounts];
    initializeAccounts(accounts, maxAccounts);

    string loggedInUser;
    if (!handleAuthentication(accounts, maxAccounts, loggedInUser))
    {
        printCenteredTitle("EXITING NEXUS SCHOOL SOFTWARE - NSS");
        return 0;
    }

    cout << "Enter your numeric student ID: ";
    unsigned int studentId;
    while (!(cin >> studentId))
    {
        cin.clear();
        string dump;
        getline(cin >> ws, dump);
        cout << "Invalid input. Enter digits only: ";
    }

    setSeed(studentId);

    Question questionBank[questionBankSize];
    initializeQuestionBank(questionBank, questionBankSize);

    StatisticsData statisticsData;
    initializeStatistics(statisticsData);

    int mainChoice = -1;

    while (mainChoice != 0)
    {
        showMainMenu();
        mainChoice = readMenuChoice(0, 3);

        if (mainChoice == 1)
        {
            int lessonChoice = -1;
            while (lessonChoice != 0)
            {
                showLessonsMenu();
                lessonChoice = readMenuChoice(0, 3);

                if (lessonChoice == 1)
                {
                    showHtmlLesson();
                }
                else if (lessonChoice == 2)
                {
                    showCssLesson();
                }
                else if (lessonChoice == 3)
                {
                    showJsLesson();
                }
            }
        }
        else if (mainChoice == 2)
        {
            runItTest(questionBank, statisticsData);
        }
        else if (mainChoice == 3)
        {
            showStatistics(statisticsData);
        }
    }

    printCenteredTitle("CLOSING NEXUS SCHOOL SOFTWARE - NSS");
    return 0;
}

