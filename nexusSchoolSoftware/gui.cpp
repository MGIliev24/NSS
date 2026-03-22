#include <iostream>
#include <string>
#include "gui.h"
#include "colors.h"

using namespace std;

// Displays the main menu screen with all primary navigation options
void showMainMenu()
{
    clearScreen();
    printAsciiTitle();
    // List all available menu options
    cout << " 1. Lessons\n";
    cout << " 2. Take IT Test\n";
    cout << " 3. View Statistics\n";
    cout << " 0. Exit\n";
    printThinLine();
    cout << "Choose option: ";
}
// Displays the lessons submenu, listing all available lesson modules
void showLessonsMenu()
{
    clearScreen();
    printCenteredTitle("LESSON MODULES");
    // List all available lesson topics
    cout << " 1. HTML Basics\n";
    cout << " 2. CSS Basics\n";
    cout << " 3. JavaScript Basics\n";
    cout << " 0. Back to Main Menu\n";
    printThinLine();
    cout << "Choose lesson: ";
}
// Pauses the current screen and waits for the user to type 0 before navigating back
void waitForEnter()
{
    cout << "\nType 0 and press Enter to go back: ";
    string dummy;
    cin >> dummy;
}

