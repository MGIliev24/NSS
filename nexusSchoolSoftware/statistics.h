#ifndef STATISTICS_H
#define STATISTICS_H
#include <string>
using namespace std;

// Stores cumulative test results for a single user across all sessions
struct StatisticsData
{
    int    totalTests;
    double highestGrade;
    double lowestGrade;
    double sumOfGrades;
    int    htmlCorrect;
    int    htmlTotal;
    int    cssCorrect;
    int    cssTotal;
    int    jsCorrect;
    int    jsTotal;
};

// Forward declaration — lets us use UserAccount* in the signature without
// including auth.h here (which would create a circular dependency).
struct UserAccount;

void initializeStatistics(StatisticsData& stats);
void updateOverallStatistics(StatisticsData& stats, double grade);

// Shows the logged-in user's personal stats plus a cross-user leaderboard
void showStatistics(UserAccount accounts[], int accountCount,
    const string& currentUser);

#endif