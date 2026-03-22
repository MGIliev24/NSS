#ifndef COLORS_H
#define COLORS_H
#include <string>
using namespace std;

string getRoseColor();
string getMintColor();
string getYellowColor();
string getResetColor();

void clearScreen();
void hideCursor();
void showCursor();

void printThickLine();
void printThinLine();
void printCenteredText(const string& text);
void printCenteredTitle(const string& title);
void printSectionTitle(const string& title);
void printMenuOption(const string& text);
void printLabelValue(const string& label, const string& value);
void printAsciiTitle();

// items = array of label strings, count = number of items
// returns 0-based index of chosen item
int arrowMenu(const string items[], int count);

// prints a centered prompt, reads one word, returns it
string centeredInput(const string& prompt);

#endif