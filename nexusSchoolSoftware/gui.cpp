#include <iostream>
#include <string>
#include "gui.h"
#include "colors.h"

using namespace std;

// Renders the main menu and returns the index of the chosen option:
//   0 = Lessons | 1 = Take IT Test | 2 = View Statistics | 3 = Homework | 4 = Log out
int showMainMenu()
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("MAIN MENU");
    cout << "\n";

    string options[5];
    options[0] = "Lessons";
    options[1] = "Take IT Test";
    options[2] = "View Statistics";
    options[3] = "Homework";
    options[4] = "Log out";
    int idx = arrowMenu(options, 5);
    cout << "\n";
    return idx;
}

// Renders the lesson selection menu and returns the index of the chosen module:
//   0 = HTML | 1 = CSS | 2 = JavaScript | 3 = Back
int showLessonsMenu()
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("LESSON MODULES");
    cout << "\n";

    string options[4];
    options[0] = "HTML Basics";
    options[1] = "CSS Basics";
    options[2] = "JavaScript Basics";
    options[3] = "Back to Main Menu";
    int idx = arrowMenu(options, 4);
    cout << "\n";
    return idx;
}

// Blocks until the user presses Enter; used at the end of lessons and result screens
void waitForEnter()
{
    cout << "\n";
    printCenteredText("Press Enter to go back...");
    showCursor();
    cin.ignore(1000, '\n');   // flush any leftover newline
    cin.get();                // wait for Enter
}