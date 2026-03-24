#pragma once
#include <string>
using namespace std;

struct StatisticsData {
    int    totalTests = 0;
    double highestGrade = 2.0;
    double lowestGrade = 6.0;
    double sumOfGrades = 0.0;
    int htmlCorrect = 0, htmlTotal = 0;
    int cssCorrect = 0, cssTotal = 0;
    int jsCorrect = 0, jsTotal = 0;
};

struct UserAccount;

void initializeStatistics(StatisticsData& s);
void updateOverallStatistics(StatisticsData& s, double grade);

struct App;
void DrawStats(App& a);