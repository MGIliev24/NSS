#pragma once
#include <string>
#include "statistics.h"
#include "homework.h"
using namespace std;

struct UserAccount {
    string username, password;
    bool   used = false;
    StatisticsData personalStats;
    HomeworkRecord homeworkRecords[homeworkCount];
};

const int maxAccounts = 10;

void initializeAccounts(UserAccount accounts[], int size);
int findUserIndex(UserAccount accounts[], int size, const string& username);

// Forward declaration avoids circular dependencies
struct App;
void DrawAuth(App& a);