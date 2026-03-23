#include <iostream>
#include <string>
#include "gui.h"
#include "colors.h"
using namespace std;

// Renders the main menu and returns the index of the option the user selected:
//   0 = Lessons  |  1 = Take IT Test  |  2 = View Statistics  |  3 = Exit
int showMainMenu()
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("MAIN MENU");
    cout << "\n";

    string options[4];
    options[0] = "Lessons";
    options[1] = "Take IT Test";
    options[2] = "View Statistics";
    options[3] = "Exit";

    int idx = arrowMenu(options, 4);
    cout << "\n";
    return idx;
}

// Renders the lesson selection menu and returns the index of the chosen module
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

// Pauses execution and waits for the user to press Enter before continuing.
// Typically called at the end of a lesson or results screen so the user can
// read the content at their own pace before being returned to the menu.
void waitForEnter()
{
    cout << "\n";
    printCenteredText("Press Enter to go back...");
    showCursor();
    cin.ignore(1000, '\n');  // Flush any leftover newline from a previous cin >> read
    cin.get();               // Block until the user actually presses