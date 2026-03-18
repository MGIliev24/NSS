#include <iostream>
#include <string>
#include "gui.h"
#include "colors.h"

using namespace std;

void showMainMenu()
{
    clearScreen();
    printAsciiTitle();
    cout << " 1. Lessons\n";
    cout << " 2. Take IT Test\n";
    cout << " 3. View Statistics\n";
    cout << " 0. Exit\n";
    printThinLine();
    cout << "Choose option: ";
}

void showLessonsMenu()
{
    clearScreen();
    printCenteredTitle("LESSON MODULES");
    cout << " 1. HTML Basics\n";
    cout << " 2. CSS Basics\n";
    cout << " 3. JavaScript Basics\n";
    cout << " 0. Back to Main Menu\n";
    printThinLine();
    cout << "Choose lesson: ";
}

void waitForEnter()
{
    cout << "\nType 0 and press Enter to go back: ";
    string dummy;
    cin >> dummy;
}

