#include <iostream>
#include <string>
#include "colors.h"
using namespace std;

// Raw Windows key read without conio.h or any extra header.
// We only need the two WinAPI calls: GetStdHandle + ReadConsoleInput.
// These are declared in <windows.h> but we forward-declare just what we need
// so we don't pull in the whole header.
#ifndef _WINDOWS_
extern "C" {
    void* __stdcall GetStdHandle(unsigned long nStdHandle);
    int   __stdcall ReadConsoleInputA(void* hConsoleInput,
        void* lpBuffer,
        unsigned long nLength,
        unsigned long* lpNumberOfEventsRead);
}
#define STD_INPUT_HANDLE ((unsigned long)-10)
// INPUT_RECORD layout (only the fields we care about)
struct KEY_EVENT_RECORD_MINI {
    int    bKeyDown;
    short  wRepeatCount;
    short  wVirtualKeyCode;
    short  wVirtualScanCode;
    union { char AsciiChar; short UnicodeChar; } uChar;
    unsigned long dwControlKeyState;
};
struct INPUT_RECORD_MINI {
    short EventType;   // 1 = KEY_EVENT
    char  _pad[2];
    KEY_EVENT_RECORD_MINI Event;
};
#define KEY_EVENT 1
#define VK_UP     0x26
#define VK_DOWN   0x28
#define VK_RETURN 0x0D
#endif

// ─── LAYOUT ───────────────────────────────────────────────────────────────────
static const int BOX_WIDTH = 92;
static const int SCREEN_WIDTH = 120;
static const int LEFT_MARGIN = (SCREEN_WIDTH - BOX_WIDTH) / 2;

static string margin() { return string(LEFT_MARGIN, ' '); }
static string pad(int n) { return n > 0 ? string(n, ' ') : ""; }

// ─── COLORS ───────────────────────────────────────────────────────────────────
string getRoseColor() { return "\033[38;5;204m"; }
string getMintColor() { return "\033[38;5;121m"; }
string getYellowColor() { return "\033[38;5;220m"; }
string getResetColor() { return "\033[0m"; }

// ─── SCREEN ───────────────────────────────────────────────────────────────────
void clearScreen() { cout << "\033[2J\033[1;1H"; }
void hideCursor() { cout << "\033[?25l"; cout.flush(); }
void showCursor() { cout << "\033[?25h"; cout.flush(); }

// ─── LINES ────────────────────────────────────────────────────────────────────
void printThickLine()
{
    cout << getMintColor() << margin() << string(BOX_WIDTH, '=') << "\n" << getResetColor();
}
void printThinLine()
{
    cout << getRoseColor() << margin() << string(BOX_WIDTH, '-') << "\n" << getResetColor();
}

// ─── TEXT ─────────────────────────────────────────────────────────────────────
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

// ─── ASCII TITLE ──────────────────────────────────────────────────────────────
void printAsciiTitle()
{
    const string lines[] =
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

// ─── ARROW-KEY MENU ───────────────────────────────────────────────────────────
int arrowMenu(const string items[], int count)
{
    hideCursor();
    int selected = 0;

    cout << "\033[s";   // save cursor position

    auto draw = [&]()
        {
            cout << "\033[u";   // restore cursor
            for (int i = 0; i < count; i++)
            {
                string arrow = (i == selected)
                    ? getRoseColor() + " >  " + getResetColor()
                    : "    ";
                cout << margin() << pad(4)
                    << arrow
                    << getMintColor() << items[i] << getResetColor()
                    << "          \n";
            }
            cout.flush();
        };

    draw();

    void* hIn = GetStdHandle(STD_INPUT_HANDLE);
    while (true)
    {
        INPUT_RECORD_MINI rec;
        unsigned long read = 0;
        ReadConsoleInputA(hIn, &rec, 1, &read);

        if (rec.EventType == KEY_EVENT && rec.Event.bKeyDown)
        {
            short vk = rec.Event.wVirtualKeyCode;
            if (vk == VK_UP) { selected = (selected - 1 + count) % count; draw(); }
            else if (vk == VK_DOWN) { selected = (selected + 1) % count;          draw(); }
            else if (vk == VK_RETURN) { cout << "\n"; showCursor(); return selected; }
        }
    }
}

// ─── CENTERED INPUT ──────────────────────────────────────────────────────────
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
