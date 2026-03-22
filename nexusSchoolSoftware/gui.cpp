#include <iostream>
#include <string>
#include "gui.h"
#include "colors.h"

using namespace std;

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

void waitForEnter()
{
    cout << "\n";
    printCenteredText("Press Enter to go back...");
    showCursor();
    cin.ignore(1000, '\n');
    cin.get();
}