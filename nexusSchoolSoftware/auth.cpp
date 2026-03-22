#include <iostream>
#include <string>
#include "auth.h"
#include "colors.h"

using namespace std;

void initializeAccounts(UserAccount accounts[], int size)
{
    for (int i = 0; i < size; i++)
    {
        accounts[i].username = "";
        accounts[i].password = "";
        accounts[i].used = false;
    }
}

static int findAccountIndex(UserAccount accounts[], int size, const string& username)
{
    for (int i = 0; i < size; i++)
    {
        if (accounts[i].used && accounts[i].username == username)
            return i;
    }
    return -1;
}

static bool signUp(UserAccount accounts[], int size, string& loggedInUser)
{
    string username = centeredInput("Choose username: ");

    if (findAccountIndex(accounts, size, username) != -1)
    {
        printCenteredText("Username already exists.");
        return false;
    }

    int freeIndex = -1;
    for (int i = 0; i < size; i++)
    {
        if (!accounts[i].used)
        {
            freeIndex = i;
            break;
        }
    }

    if (freeIndex == -1)
    {
        printCenteredText("No free slots.");
        return false;
    }

    string password = centeredInput("Choose password: ");
    accounts[freeIndex].username = username;
    accounts[freeIndex].password = password;
    accounts[freeIndex].used = true;
    loggedInUser = username;
    printCenteredText("Account created!  Welcome, " + username + ".");
    return true;
}

static bool logIn(UserAccount accounts[], int size, string& loggedInUser)
{
    string username = centeredInput("Username: ");
    string password = centeredInput("Password: ");

    int index = findAccountIndex(accounts, size, username);
    if (index == -1)
    {
        printCenteredText("No such user.");
        return false;
    }
    if (accounts[index].password != password)
    {
        printCenteredText("Wrong password.");
        return false;
    }

    loggedInUser = username;
    printCenteredText("Welcome back, " + username + "!");
    return true;
}

bool handleAuthentication(UserAccount accounts[], int size, string& loggedInUser)
{
    bool loggedIn = false;
    while (!loggedIn)
    {
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("LOGIN PANEL");
        cout << "\n";

        string options[3];
        options[0] = "Sign up";
        options[1] = "Log in";
        options[2] = "Exit";
        int choice = arrowMenu(options, 3);
        cout << "\n";

        if (choice == 0)
            loggedIn = signUp(accounts, size, loggedInUser);
        else if (choice == 1)
            loggedIn = logIn(accounts, size, loggedInUser);
        else
            return false;
    }
    return true;
}