#include <iostream>
#include <iomanip>
#include <string>
#include "statistics.h"
#include "colors.h"
#include "gui.h"

using namespace std;

void initializeStatistics(StatisticsData& stats)
{ // Set initial values for statistics
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
{ // Update overall statistics with a new test result
    stats.totalTests++;
    stats.sumOfGrades += grade;
    if (grade > stats.highestGrade) stats.highestGrade = grade;
    if (grade < stats.lowestGrade)  stats.lowestGrade = grade;
}

void showStatistics(const StatisticsData& stats)
{ // Display the statistics in a user-friendly format
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("SYSTEM STATISTICS");

    if (stats.totalTests == 0)
    {
        printCenteredText("No tests have been completed yet.");
        waitForEnter();
        return;
    }
	
    double averageGrade = stats.sumOfGrades / stats.totalTests;
	// Display overall statistics
    printSectionTitle("Overall");
    printLabelValue("Total tests taken", to_string(stats.totalTests));
    printLabelValue("Highest grade    ", to_string(stats.highestGrade).substr(0, 4));
    printLabelValue("Lowest grade     ", to_string(stats.lowestGrade).substr(0, 4));
    printLabelValue("Average grade    ", to_string(averageGrade).substr(0, 4));

    double htmlPct = stats.htmlTotal > 0 ? (double)stats.htmlCorrect / stats.htmlTotal * 100.0 : 0.0;
    double cssPct = stats.cssTotal > 0 ? (double)stats.cssCorrect / stats.cssTotal * 100.0 : 0.0;
    double jsPct = stats.jsTotal > 0 ? (double)stats.jsCorrect / stats.jsTotal * 100.0 : 0.0;
	// Display category performance statistics
    printSectionTitle("Category Performance");
    printLabelValue("HTML      ", to_string((int)htmlPct) + "%");
    printLabelValue("CSS       ", to_string((int)cssPct) + "%");
    printLabelValue("JavaScript", to_string((int)jsPct) + "%");

    string best = "None";
    string worst = "None";
    double bestV = -1.0;
    double worstV = 101.0;
	// Determine best and worst categories based on percentage correct
    if (stats.htmlTotal > 0)
    {
        if (htmlPct > bestV) { bestV = htmlPct; best = "HTML"; }
        if (htmlPct < worstV) { worstV = htmlPct; worst = "HTML"; }
    }
    if (stats.cssTotal > 0)
    {
        if (cssPct > bestV) { bestV = cssPct; best = "CSS"; }
        if (cssPct < worstV) { worstV = cssPct; worst = "CSS"; }
    }
    if (stats.jsTotal > 0)
    {
        if (jsPct > bestV) { bestV = jsPct; best = "JavaScript"; }
        if (jsPct < worstV) { worstV = jsPct; worst = "JavaScript"; }
    }

    if (best != "None")
    {
        printSectionTitle("Highlights");
        printLabelValue("Best category   ", best);
        printLabelValue("Weakest category", worst);
    }

    cout << "\n";
    waitForEnter();
}