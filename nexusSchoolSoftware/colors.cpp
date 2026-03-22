#include <iostream>
#include <string>
#include <windows.h>
#include "colors.h"

using namespace std;

static const int BOX_WIDTH = 92;
static const int SCREEN_WIDTH = 120;
static const int LEFT_MARGIN = (SCREEN_WIDTH - BOX_WIDTH) / 2;

static string margin()
{
    return string(LEFT_MARGIN, ' ');
}

static string pad(int n)
{
    if (n > 0) return string(n, ' ');
    return "";
}

string getRoseColor() { return "\033[38;5;204m"; }
string getMintColor() { return "\033[38;5;121m"; }
string getYellowColor() { return "\033[38;5;220m"; }
string getResetColor() { return "\033[0m"; }

void clearScreen() { cout << "\033[2J\033[1;1H"; }
void hideCursor() { cout << "\033[?25l"; cout.flush(); }
void showCursor() { cout << "\033[?25h"; cout.flush(); }

void printThickLine()
{
    cout << getMintColor() << margin() << string(BOX_WIDTH, '=') << "\n" << getResetColor();
}

void printThinLine()
{
    cout << getRoseColor() << margin() << string(BOX_WIDTH, '-') << "\n" << getResetColor();
}

void printCenteredText(const string& text)
{
    int p = (BOX_WIDTH - (int)text.length()) / 2;
    cout << margin() << pad(p) << text << "\n";
}

void printCenteredTitle(const string& title)
{
    printThickLine();
    cout << getMintColor();
    printCenteredText(title);
    cout << getResetColor();
    printThickLine();
}

void printSectionTitle(const string& title)
{
    cout << "\n";
    printThinLine();
    cout << getRoseColor();
    printCenteredText(title);
    cout << getResetColor();
    printThinLine();
}

void printMenuOption(const string& text)
{
    cout << getMintColor() << margin() << pad(6) << text << "\n" << getResetColor();
}

void printLabelValue(const string& label, const string& value)
{
    cout << margin() << pad(4)
        << getRoseColor() << label << getResetColor()
        << " : "
        << getMintColor() << value << getResetColor() << "\n";
}

void printAsciiTitle()
{   //logo
    const string lines[4] =
    {
        " _____                            _           _            ___ _                     ",
        "|   | |___ _ _ _ _ ___    ___ ___| |_ ___ ___| |   ___ ___|  _| |_ _ _ _ ___ ___ ___ ",
        "| | | | -_|_'_| | |_ -|  |_ -|  _|   | . | . | |  |_ -| . |  _|  _| | | | .'|  _| -_|",
        "|_|___|___|_,_|___|___|  |___|___|_|_|___|___|_|  |___|___|_| |_| |_____|__,|_| |___|"
    };
    cout << getRoseColor();
    for (int i = 0; i < 4; i++)
    {
        int p = (BOX_WIDTH - (int)lines[i].length()) / 2;
        if (p < 0) p = 0;
        cout << margin() << pad(p) << lines[i] << "\n";
    }
    cout << getResetColor();
    printThickLine();
}

int arrowMenu(const string items[], int count)
{
    hideCursor();
    int selected = 0;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD outMode = 0;
    GetConsoleMode(hOut, &outMode);
    SetConsoleMode(hOut, outMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD oldInMode = 0;
    GetConsoleMode(hIn, &oldInMode);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS);

    cout << "\033[s";

    // draw all items
    for (int i = 0; i < count; i++)
    {
        string arrow = (i == selected)
            ? getRoseColor() + " >  " + getResetColor()
            : "    ";
        cout << margin() << pad(4) << arrow
            << getMintColor() << items[i] << getResetColor()
            << "          \n";
    }
    cout.flush();

    bool running = true;
    while (running)
    {
        INPUT_RECORD rec;
        DWORD readCount = 0;
        ReadConsoleInput(hIn, &rec, 1, &readCount);

        if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown)
        {
            WORD vk = rec.Event.KeyEvent.wVirtualKeyCode;

            if (vk == VK_UP)
                selected = (selected - 1 + count) % count;
            else if (vk == VK_DOWN)
                selected = (selected + 1) % count;
            else if (vk == VK_RETURN)
            {
                running = false;
                break;
            }

            // redraw
            cout << "\033[u";
            for (int i = 0; i < count; i++)
            {
                string arrow = (i == selected)
                    ? getRoseColor() + " >  " + getResetColor()
                    : "    ";
                cout << margin() << pad(4) << arrow
                    << getMintColor() << items[i] << getResetColor()
                    << "          \n";
            }
            cout.flush();
        }
    }

    cout << "\n";
    showCursor();
    SetConsoleMode(hIn, oldInMode);
    return selected;
}

string centeredInput(const string& prompt)
{
    showCursor();
    printCenteredText(prompt);
    cout << margin() << pad((BOX_WIDTH - 20) / 2);
    cout.flush();
    string value;
    cin >> value;
    cin.ignore(1000, '\n');
    return value;
}