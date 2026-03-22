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
    if (grade > stats.highestGrade) stats.highestGrade = grade;
    if (grade < stats.lowestGrade) stats.lowestGrade = grade;
}

void showStatistics(const StatisticsData& stats)
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("SYSTEM STATISTICS");

    if (stats.totalTests == 0)
    {
        printCenteredText("No tests have been completed yet.");
        waitForEnter();
        return;
    }

    cout << fixed << setprecision(2);
    double averageGrade = stats.sumOfGrades / stats.totalTests;

    printSectionTitle("Overall");
    printLabelValue("Total tests taken", to_string(stats.totalTests));
    printLabelValue("Highest grade    ", to_string(stats.highestGrade).substr(0, 4));
    printLabelValue("Lowest grade     ", to_string(stats.lowestGrade).substr(0, 4));
    printLabelValue("Average grade    ", to_string(averageGrade).substr(0, 4));

    double htmlPct = stats.htmlTotal > 0 ? (double)stats.htmlCorrect / stats.htmlTotal * 100.0 : 0.0;
    double cssPct = stats.cssTotal > 0 ? (double)stats.cssCorrect / stats.cssTotal * 100.0 : 0.0;
    double jsPct = stats.jsTotal > 0 ? (double)stats.jsCorrect / stats.jsTotal * 100.0 : 0.0;

    printSectionTitle("Category Performance");

    auto pctStr = [](double v) {
        // format "XX.XX%"
        string s = to_string((int)v) + "." + to_string((int)(v * 100) % 100 / 10) + to_string((int)(v * 100) % 10) + "%";
        return s;
        };

    printLabelValue("HTML      ", pctStr(htmlPct));
    printLabelValue("CSS       ", pctStr(cssPct));
    printLabelValue("JavaScript", pctStr(jsPct));

    // Best / worst
    string best = "None", worst = "None";
    double bestV = -1.0, worstV = 101.0;

    auto check = [&](double pct, const string& name, int total) {
        if (total == 0) return;
        if (pct > bestV) { bestV = pct; best = name; }
        if (pct < worstV) { worstV = pct; worst = name; }
        };

    check(htmlPct, "HTML", stats.htmlTotal);
    check(cssPct, "CSS", stats.cssTotal);
    check(jsPct, "JavaScript", stats.jsTotal);

    if (best != "None")
    {
        printSectionTitle("Highlights");
        printLabelValue("Best category   ", best);
        printLabelValue("Weakest category", worst);
    }

    cout << "\n";
    waitForEnter();
}
