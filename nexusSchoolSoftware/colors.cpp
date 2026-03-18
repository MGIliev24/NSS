#include <iostream>
#include <string>
#include "colors.h"

using namespace std;

void printThickLine()
{
    cout << "============================================================\n";
}

void printThinLine()
{
    cout << "------------------------------------------------------------\n";
}

void printCenteredTitle(const string &title)
{
    int width = 60;
    int titleLength = (int)title.length();
    int leftSpaces = (width - titleLength) / 2;

    printThickLine();
    for (int i = 0; i < leftSpaces; i++)
    {
        cout << " ";
    }
    cout << title << "\n";
    printThickLine();
}

void printSectionTitle(const string &title)
{
    cout << "\n";
    printThinLine();
    cout << title << "\n";
    printThinLine();
}

void clearScreen()
{
    // Clear screen using ANSI escape codes and move cursor to top
    cout << "\x1B[2J\x1B[H";
}

void printAsciiTitle()
{
    cout << " _   _                                _                 _ \n";
    cout << "| \\ | |                              | |               | |\n";
    cout << "|  \\| | _____  ___   _ ___   ___  ___| |__   ___   ___ | |\n";
    cout << "| . ` |/ _ \\\\ \\/ | | | / __| / __|/ __| '_ \\\\ / _ \\\\ / _ \\\\| |\n";
    cout << "| |\\\\  |  __/>  <| |_| \\\\__ \\\\ \\\\__ | (__| | | | (_) | (_) | |\n";
    cout << "\\_| \\\\_/\\\\___/_/\\\\_\\\\__,_|___/ |___/\\\\___|_| |_|\\\\___/ \\\\___/|_|\n";
    cout << "           / _| |                                         \n";
    cout << " ___  ___ | |_| |___      ____ _ _ __ ___                 \n";
    cout << "/ __|/ _ \\\\|  _| __\\\\ \\\\ /\\\\ / / _` | '__/ _ \\\\                \n";
    cout << "\\\\__ | (_) | | | |_ \\\\ V  V | (_| | | |  __/                \n";
    cout << "|___/\\\\___/|_|  \\\\__| \\\\_/\\\\_/ \\\\__,_|_|  \\\\___|                \n";
    printThickLine();
    cout << "                    NEXUS SCHOOL SOFTWARE - NSS\n";
    printThickLine();
}

