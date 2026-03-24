#ifndef AUTH_H
#define AUTH_H
#include <string>
#include "statistics.h"
#include "homework.h"
using namespace std;

// Holds everything tied to a single registered user
struct UserAccount
{
    string         username;
    string         password;
    bool           used;                               // false = empty slot
    StatisticsData personalStats;                      // per-user test history
    HomeworkRecord homeworkRecords[homeworkCount];     // per-user homework status
};

const int maxAccounts = 10;

void initializeAccounts(UserAccount accounts[], int size);

// Returns the array index of the account whose username matches, or -1
int findUserIndex(UserAccount accounts[], int size, const string& username);

// Runs the login / sign-up loop; returns true when a user is logged in
bool handleAuthentication(UserAccount accounts[], int size, string& loggedInUser);

#endif