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
    // Set up accounts and require login before anything else
    UserAccount accounts[maxAccounts];
    initializeAccounts(accounts, maxAccounts);
    string loggedInUser;

    // If the user exits the auth screen without logging in, close the app cleanly
    if (!handleAuthentication(accounts, maxAccounts, loggedInUser))
    {
		clearScreen(); // Clear the screen before showing the goodbye message
		printAsciiTitle();  
		printCenteredTitle("GOODBYE");  // Show a goodbye message if the user exits from the authentication screen
        printCenteredText("Exiting Nexus School Software.  See you next time!");
        cout << "\n";
        return 0;
    }

    // Use the student ID as a seed so question order is consistent per student
    clearScreen();
    printAsciiTitle();
	printCenteredTitle("STUDENT ID"); // Prompt the user for their student ID to use as a seed for randomization
    string idStr = centeredInput("Enter your numeric student ID: ");
    unsigned int studentId = 0;

    // Parse the ID manually to strip any non-numeric characters
    for (int i = 0; i < (int)idStr.length(); i++)
    {
        if (idStr[i] >= '0' && idStr[i] <= '9')
            studentId = studentId * 10 + (unsigned int)(idStr[i] - '0');
    }
    if (studentId == 0) studentId = 1;  // Fallback in case input was entirely non-numeric
    setSeed(studentId);

    // Initialize the question bank and blank statistics for this session
    Question questionBank[questionBankSize];
    initializeQuestionBank(questionBank, questionBankSize);
    StatisticsData statisticsData;
    initializeStatistics(statisticsData);

    // Main navigation loop — exits when the user selects "Exit" (index 3)
    int mainChoice = -1;
    while (mainChoice != 3)
    {
        mainChoice = showMainMenu();
        if (mainChoice == 0)
        {
            // Lesson sub-loop — stays inside the lessons menu until "Back" is chosen
            int lessonChoice = -1;
            while (lessonChoice != 3)
			{   // Show the lessons menu and call the appropriate function based on the user's choice
                lessonChoice = showLessonsMenu();
                if (lessonChoice == 0)      showHtmlLesson();
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