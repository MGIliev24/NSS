#ifndef STATISTICS_H
#define STATISTICS_H

struct StatisticsData
{
    int totalTests;
    double highestGrade;
    double lowestGrade;
    double sumOfGrades;

    int htmlCorrect;
    int htmlTotal;
    int cssCorrect;
    int cssTotal;
    int jsCorrect;
    int jsTotal;
};

void initializeStatistics(StatisticsData& stats);
void updateOverallStatistics(StatisticsData& stats, double grade);
void showStatistics(const StatisticsData& stats);

#endif


