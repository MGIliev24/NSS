#include <iostream>
#include <iomanip>
#include <string>
#include "statistics.h"
#include "colors.h"
#include "gui.h"

using namespace std;

void initializeStatistics(StatisticsData& stats)
{
    stats.totalTests = 0;
    stats.highestGrade = 2.0;
    stats.lowestGrade = 6.0;
    stats.sumOfGrades = 0.0;
    stats.htmlCorrect = 0;
    stats.htmlTotal = 0;
    stats.cssCorrect = 0;
    stats.cssTotal = 0;
    stats.jsCorrect = 0;
    stats.jsTotal = 0;
}

void updateOverallStatistics(StatisticsData& stats, double grade)
{
    stats.totalTests++;
    stats.sumOfGrades += grade;
    if (grade > stats.highestGrade)
    {
        stats.highestGrade = grade;
    }
    if (grade < stats.lowestGrade)
    {
        stats.lowestGrade = grade;
    }
}

void showStatistics(const StatisticsData& stats)
{
    clearScreen();
    printCenteredTitle("SYSTEM STATISTICS");

    if (stats.totalTests == 0)
    {
        cout << "No tests have been completed yet.\n";
        waitForEnter();
        return;
    }

    double averageGrade = stats.sumOfGrades / stats.totalTests;

    cout << fixed << setprecision(2);
    cout << "Total tests taken : " << stats.totalTests << "\n";
    cout << "Highest grade     : " << stats.highestGrade << "\n";
    cout << "Lowest grade      : " << stats.lowestGrade << "\n";
    cout << "Average grade     : " << averageGrade << "\n\n";

    printSectionTitle("Category performance");

    double htmlPercent = 0.0;
    double cssPercent = 0.0;
    double jsPercent = 0.0;

    if (stats.htmlTotal > 0)
    {
        htmlPercent = (double)stats.htmlCorrect / (double)stats.htmlTotal * 100.0;
    }
    if (stats.cssTotal > 0)
    {
        cssPercent = (double)stats.cssCorrect / (double)stats.cssTotal * 100.0;
    }
    if (stats.jsTotal > 0)
    {
        jsPercent = (double)stats.jsCorrect / (double)stats.jsTotal * 100.0;
    }

    cout << "HTML       : " << htmlPercent << "%\n";
    cout << "CSS        : " << cssPercent << "%\n";
    cout << "JavaScript : " << jsPercent << "%\n\n";

    string bestCategory = "None";
    string worstCategory = "None";
    double bestValue = -1.0;
    double worstValue = 101.0;

    if (stats.htmlTotal > 0)
    {
        if (htmlPercent > bestValue)
        {
            bestValue = htmlPercent;
            bestCategory = "HTML";
        }
        if (htmlPercent < worstValue)
        {
            worstValue = htmlPercent;
            worstCategory = "HTML";
        }
    }

    if (stats.cssTotal > 0)
    {
        if (cssPercent > bestValue)
        {
            bestValue = cssPercent;
            bestCategory = "CSS";
        }
        if (cssPercent < worstValue)
        {
            worstValue = cssPercent;
            worstCategory = "CSS";
        }
    }

    if (stats.jsTotal > 0)
    {
        if (jsPercent > bestValue)
        {
            bestValue = jsPercent;
            bestCategory = "JavaScript";
        }
        if (jsPercent < worstValue)
        {
            worstValue = jsPercent;
            worstCategory = "JavaScript";
        }
    }

    if (bestCategory != "None")
    {
        cout << "Best category   : " << bestCategory << "\n";
        cout << "Weakest category: " << worstCategory << "\n";
    }

    waitForEnter();
}

