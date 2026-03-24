#include <iostream>
#include <string>
#include "colors.h"
#include "gui.h"
#include "question.h"
#include "test.h"
#include "statistics.h"
#include "randomizer.h"
#include "auth.h"
#include "homework.h"

using namespace std;

int main()
{
    // ── One-time setup ────────────────────────────────────────────────────────
    UserAccount accounts[maxAccounts];
    initializeAccounts(accounts, maxAccounts);   // blank all account slots

    HomeworkAssignment homeworkAssignments[homeworkCount];
    initializeHomeworkAssignments(homeworkAssignments);  // set up the 3 assignments

    Question questionBank[questionBankSize];
    initializeQuestionBank(questionBank, questionBankSize);

    // ── Outer loop: runs until the user chooses Exit from the login screen ────
    bool appRunning = true;
    while (appRunning)
    {
        string loggedInUser = "";

        // Show the login / sign-up screen.
        // Returns false only when the user picks "Exit" from the auth menu.
        if (!handleAuthentication(accounts, maxAccounts, loggedInUser))
        {
            clearScreen();
            printAsciiTitle();
            printCenteredTitle("GOODBYE");
            printCenteredText("Exiting Nexus School Software.  See you next time!");
            cout << "\n";
            appRunning = false;
            break;
        }

        // Ask for a numeric student ID to seed the randomiser
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("STUDENT ID");
        string idStr = centeredInput("Enter your numeric student ID: ");

        unsigned int studentId = 0;
        for (int i = 0; i < (int)idStr.length(); i++)
            if (idStr[i] >= '0' && idStr[i] <= '9')
                studentId = studentId * 10 + (unsigned int)(idStr[i] - '0');
        if (studentId == 0) studentId = 1;  // guard against empty input
        setSeed(studentId);

        // ── Inner loop: main menu for the logged-in session ───────────────────
        // Returns when the user selects "Log out" (index 4).
        int mainChoice = -1;
        while (mainChoice != 4)
        {
            mainChoice = showMainMenu();   // 0-Lessons 1-Test 2-Stats 3-HW 4-Logout

            if (mainChoice == 0)
            {
                // Lesson sub-loop
                int lessonChoice = -1;
                while (lessonChoice != 3)
                {
                    lessonChoice = showLessonsMenu();
                    if (lessonChoice == 0) showHtmlLesson();
                    else if (lessonChoice == 1) showCssLesson();
                    else if (lessonChoice == 2) showJsLesson();
                }
            }
            else if (mainChoice == 1)
            {
                // Run the test using this user's personal statistics
                int userIdx = findUserIndex(accounts, maxAccounts, loggedInUser);
                if (userIdx != -1)
                    runItTest(questionBank, accounts[userIdx].personalStats);
            }
            else if (mainChoice == 2)
            {
                // Show this user's stats plus the cross-user leaderboard
                showStatistics(accounts, maxAccounts, loggedInUser);
            }
            else if (mainChoice == 3)
            {
                // Show the homework hub for this user
                int userIdx = findUserIndex(accounts, maxAccounts, loggedInUser);
                if (userIdx != -1)
                    showHomeworkMenu(accounts[userIdx].homeworkRecords,
                        homeworkAssignments,
                        questionBank);
            }
            // mainChoice == 4: Log out — loop condition ends the inner while
        }

        // Brief logout confirmation before returning to the auth screen
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("LOGGED OUT");
        printCenteredText("Goodbye, " + loggedInUser + "!  See you next time.");
        cout << "\n";
    }

    return 0;
}