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
    string options[] = { "Lessons", "Take IT Test", "View Statistics", "Exit" };
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
    string options[] = { "HTML Basics", "CSS Basics", "JavaScript Basics", "Back to Main Menu" };
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
