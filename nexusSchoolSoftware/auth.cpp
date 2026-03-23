#include <iostream>
#include <string>
#include "auth.h"
#include "colors.h"
using namespace std;

// Initializes all account slots to empty/unused state before the program starts
void initializeAccounts(UserAccount accounts[], int size)
{
    for (int i = 0; i < size; i++)
    {
        accounts[i].username = "";
        accounts[i].password = "";
        accounts[i].used = false;  // Mark slot as available
    }
}

// Searches for an account by username and returns its index, or -1 if not found
static int findAccountIndex(UserAccount accounts[], int size, const string& username)
{
    for (int i = 0; i < size; i++)
    {
        // Only check slots that are actively in use
        if (accounts[i].used && accounts[i].username == username)
            return i;
    }
    return -1;  // No matching account found
}

// Handles new user registration; sets loggedInUser on success and returns true
static bool signUp(UserAccount accounts[], int size, string& loggedInUser)
{
    string username = centeredInput("Choose username: ");

    // Reject registration if the username is already taken
    if (findAccountIndex(accounts, size, username) != -1)
    {
        printCenteredText("Username already exists.");
        return false;
    }

    // Find the first available (unused) account slot
    int freeIndex = -1;
    for (int i = 0; i < size; i++)
    {
        if (!accounts[i].used)
        {
            freeIndex = i;
            break;
        }
    }

    // No room left for a new account
    if (freeIndex == -1)
    {
        printCenteredText("No free slots.");
        return false;
    }

    string password = centeredInput("Choose password: ");

    // Store the new account in the free slot and mark it as used
    accounts[freeIndex].username = username;
    accounts[freeIndex].password = password;
    accounts[freeIndex].used = true;

    loggedInUser = username;
    printCenteredText("Account created!  Welcome, " + username + ".");
    return true;
}

// Handles login by verifying username and password; sets loggedInUser on success
static bool logIn(UserAccount accounts[], int size, string& loggedInUser)
{
    string username = centeredInput("Username: ");
    string password = centeredInput("Password: ");

    int index = findAccountIndex(accounts, size, username);

    // Reject if no account with that username exists
    if (index == -1)
    {
        printCenteredText("No such user.");
        return false;
    }

    // Reject if the password doesn't match the stored one
    if (accounts[index].password != password)
    {
        printCenteredText("Wrong password.");
        return false;
    }

    loggedInUser = username;
    printCenteredText("Welcome back, " + username + "!");
    return true;
}

// Displays the login panel and loops until the user successfully authenticates or exits
// Returns true if a user is logged in, false if they chose to exit
bool handleAuthentication(UserAccount accounts[], int size, string& loggedInUser)
{
    bool loggedIn = false;

    while (!loggedIn)
    {
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("LOGIN PANEL");
        cout << "\n";

        // Build the main menu options
        string options[3];
        options[0] = "Sign up";
        options[1] = "Log in";
        options[2] = "Exit";

        int choice = arrowMenu(options, 3);
        cout << "\n";

        if (choice == 0)
            loggedIn = signUp(accounts, size, loggedInUser);   // Attempt registration
        else if (choice == 1)
            loggedIn = logIn(accounts, size, loggedInUser);    // Attempt login
        else
            return false;  // User chose to exit the application
    }

    return true;  // Authentication succeeded
}