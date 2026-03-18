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

static int readAuthChoice(int minValue, int maxValue)
{
    int choice;
    while (true)
    {
        cout << "Enter choice (" << minValue << "-" << maxValue << "): ";
        if (cin >> choice)
        {
            if (choice >= minValue && choice <= maxValue)
            {
                return choice;
            }
        }
        cin.clear();
        string dump;
        getline(cin >> ws, dump);
        cout << "Invalid input. Try again.\n";
    }
}

static int findAccountIndex(UserAccount accounts[], int size, const string& username)
{
    for (int i = 0; i < size; i++)
    {
        if (accounts[i].used && accounts[i].username == username)
        {
            return i;
        }
    }
    return -1;
}

static bool signUp(UserAccount accounts[], int size, string& loggedInUser)
{
    string username;
    string password;

    cout << "Choose username: ";
    cin >> username;

    if (findAccountIndex(accounts, size, username) != -1)
    {
        cout << "Username already exists.\n";
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
        cout << "No free slots for new users.\n";
        return false;
    }

    cout << "Choose password: ";
    cin >> password;

    accounts[freeIndex].username = username;
    accounts[freeIndex].password = password;
    accounts[freeIndex].used = true;

    cout << "Account created. You are now logged in as " << username << ".\n";
    loggedInUser = username;
    return true;
}

static bool logIn(UserAccount accounts[], int size, string& loggedInUser)
{
    string username;
    string password;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    int index = findAccountIndex(accounts, size, username);
    if (index == -1)
    {
        cout << "No such user.\n";
        return false;
    }

    if (accounts[index].password != password)
    {
        cout << "Wrong password.\n";
        return false;
    }

    cout << "Login successful. Welcome, " << username << ".\n";
    loggedInUser = username;
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
        cout << " 1. Sign up\n";
        cout << " 2. Log in\n";
        cout << " 0. Exit\n";
        printThinLine();

        int choice = readAuthChoice(0, 2);

        if (choice == 1)
        {
            loggedIn = signUp(accounts, size, loggedInUser);
        }
        else if (choice == 2)
        {
            loggedIn = logIn(accounts, size, loggedInUser);
        }
        else if (choice == 0)
        {
            return false;
        }
    }
    return true;
}

