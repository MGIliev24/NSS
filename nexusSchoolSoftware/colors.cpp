#include <iostream>
#include <string>
#include <windows.h>
#include "colors.h"

using namespace std;

// ─── Layout constants ────────────────────────────────────────────────────────
static const int BOX_WIDTH = 92;   // Width of the content box in characters
static const int SCREEN_WIDTH = 120;  // Assumed total terminal width
static const int LEFT_MARGIN = (SCREEN_WIDTH - BOX_WIDTH) / 2;  // Centers the box

// Returns a string of spaces equal to the left margin, used before every line
static string margin()
{
    return string(LEFT_MARGIN, ' ');
}

// Returns a padding string of n spaces; returns empty string if n <= 0
static string pad(int n)
{
    if (n > 0) return string(n, ' ');
    return "";
}

// ─── ANSI color helpers ───────────────────────────────────────────────────────
// Each function returns an ANSI escape code for a specific theme color.
// Call getResetColor() after any colored output to restore the default.
string getRoseColor() { return "\033[38;5;204m"; }  // Soft rose/pink
string getMintColor() { return "\033[38;5;121m"; }  // Mint green
string getYellowColor() { return "\033[38;5;220m"; }  // Warm yellow
string getResetColor() { return "\033[0m"; }          // Resets all attributes

// ─── Terminal control ─────────────────────────────────────────────────────────
void clearScreen() { cout << "\033[2J\033[1;1H"; }  // Clears screen and moves cursor to top-left
void hideCursor() { cout << "\033[?25l"; cout.flush(); }  // Hides the blinking cursor
void showCursor() { cout << "\033[?25h"; cout.flush(); }  // Restores the blinking cursor

// ─── Line / border printers ───────────────────────────────────────────────────

// Prints a heavy '=' border line in mint — used for major titles
void printThickLine()
{
    cout << getMintColor() << margin() << string(BOX_WIDTH, '=') << "\n" << getResetColor();
}

// Prints a light '-' divider line in rose — used for section separators
void printThinLine()
{
    cout << getRoseColor() << margin() << string(BOX_WIDTH, '-') << "\n" << getResetColor();
}

// ─── Text printers ────────────────────────────────────────────────────────────

// Prints text horizontally centered within BOX_WIDTH
void printCenteredText(const string& text)
{
    int p = (BOX_WIDTH - (int)text.length()) / 2;
    cout << margin() << pad(p) << text << "\n";
}

// Prints a major title framed by thick lines (e.g. "LOGIN PANEL")
void printCenteredTitle(const string& title)
{
    printThickLine();
    cout << getMintColor();
    printCenteredText(title);
    cout << getResetColor();
    printThickLine();
}

// Prints a subsection title framed by thin lines (e.g. "INVENTORY")
void printSectionTitle(const string& title)
{
    cout << "\n";
    printThinLine();
    cout << getRoseColor();
    printCenteredText(title);
    cout << getResetColor();
    printThinLine();
}

// Prints a single menu option indented inside the box
void printMenuOption(const string& text)
{
    cout << getMintColor() << margin() << pad(6) << text << "\n" << getResetColor();
}

// Prints a label : value pair with distinct colors for each side
// e.g.  "Balance : 120"
void printLabelValue(const string& label, const string& value)
{
    cout << margin() << pad(4)
        << getRoseColor() << label << getResetColor()
        << " : "
        << getMintColor() << value << getResetColor() << "\n";
}

// Prints the hard-coded ASCII art logo, centered within the box
void printAsciiTitle()
{
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
        // Each line may have a different length, so center each one individually
        int p = (BOX_WIDTH - (int)lines[i].length()) / 2;
        if (p < 0) p = 0;  // Clamp — very long lines just start at the margin
        cout << margin() << pad(p) << lines[i] << "\n";
    }
    cout << getResetColor();
    printThickLine();
}

// ─── Arrow-key navigation menu ────────────────────────────────────────────────
// Renders a list of items and lets the user navigate with UP/DOWN arrows.
// Pressing ENTER confirms the selection. Returns the 0-based index of the chosen item.
int arrowMenu(const string items[], int count)
{
    hideCursor();
    int selected = 0;

    // Enable ANSI escape processing on the output handle (required on Windows)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD outMode = 0;
    GetConsoleMode(hOut, &outMode);
    SetConsoleMode(hOut, outMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // Switch input to raw mode so we can read individual key events
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    DWORD oldInMode = 0;
    GetConsoleMode(hIn, &oldInMode);
    SetConsoleMode(hIn, ENABLE_EXTENDED_FLAGS);

    // Save cursor position so we can redraw the menu in place on each keystroke
    cout << "\033[s";

    // Initial render of all menu items
    for (int i = 0; i < count; i++)
    {
        // Highlight the currently selected row with a rose arrow indicator
        string arrow = (i == selected)
            ? getRoseColor() + " >  " + getResetColor()
            : "    ";
        cout << margin() << pad(4) << arrow
            << getMintColor() << items[i] << getResetColor()
            << "          \n";  // Trailing spaces overwrite any leftover characters on redraw
    }
    cout.flush();

    bool running = true;
    while (running)
    {
        INPUT_RECORD rec;
        DWORD readCount = 0;
        ReadConsoleInput(hIn, &rec, 1, &readCount);

        // Only act on key-down events
        if (rec.EventType == KEY_EVENT && rec.Event.KeyEvent.bKeyDown)
        {
            WORD vk = rec.Event.KeyEvent.wVirtualKeyCode;

            if (vk == VK_UP)
                selected = (selected - 1 + count) % count;  // Wrap around to bottom
            else if (vk == VK_DOWN)
                selected = (selected + 1) % count;           // Wrap around to top
            else if (vk == VK_RETURN)
            {
                running = false;
                break;
            }

            // Restore saved cursor position and redraw the full menu in place
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
    SetConsoleMode(hIn, oldInMode);  // Restore original input mode before returning
    return selected;
}

// Displays a centered prompt, then reads a single whitespace-delimited token from stdin.
// The cursor is shown during input and the input buffer is flushed afterward.
string centeredInput(const string& prompt)
{
    showCursor();
    printCenteredText(prompt);
    cout << margin() << pad((BOX_WIDTH - 20) / 2);
    string value;
    cin >> value;
    cin.ignore();
    return value;
}