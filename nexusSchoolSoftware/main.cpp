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
// Safely reads an integer input from the user within the given [minValue, maxValue] range.
// Rejects non-numeric input and out-of-range values, prompting the user to retry.
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
        // Clear the error flag and discard the bad input before retrying
        cin.clear();
        string dump;
        getline(cin >> ws, dump);
        cout << "Invalid input. Try again.\n";
    }
}

int main()
{
    // Shows the welcome screen before any logic runs
    clearScreen();
    printAsciiTitle();
    // --- Account Setup & Authentication ---

    UserAccount accounts[maxAccounts];
    initializeAccounts(accounts, maxAccounts);

    string loggedInUser;
    if (!handleAuthentication(accounts, maxAccounts, loggedInUser))
    {
        printCenteredTitle("EXITING NEXUS SCHOOL SOFTWARE - NSS");
        return 0;
    }
    // --- Student ID & Randomizer Seed ---

   // Collect the student's numeric ID to seed the randomizer,
   // ensuring each student receives a unique question order

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
    // --- Data Initialization ---

// Load all questions into the question bank for use during tests

    Question questionBank[questionBankSize];
    initializeQuestionBank(questionBank, questionBankSize);

    StatisticsData statisticsData;
    initializeStatistics(statisticsData);
    // --- Main Navigation Loop ---

// Keep showing the main menu until the user chooses to exit (option 0)

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
            // Launch the IT test using the loaded question bank;
           // results are recorded directly into statisticsData
            runItTest(questionBank, statisticsData);
        }
        else if (mainChoice == 3)
        {
            showStatistics(statisticsData);
        }
    }
    // Exit message before the program terminates
    printCenteredTitle("CLOSING NEXUS SCHOOL SOFTWARE - NSS");
    return 0;
}

