#include <iostream>
#include <iomanip>
#include <string>
#include "auth.h"       // full UserAccount definition needed here
#include "statistics.h"
#include "colors.h"
#include "gui.h"

using namespace std;

// Sets all counters and grades to their neutral starting values
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

// Called after every test to keep the running totals up-to-date
void updateOverallStatistics(StatisticsData& stats, double grade)
{
    stats.totalTests++;
    stats.sumOfGrades += grade;
    if (grade > stats.highestGrade) stats.highestGrade = grade;
    if (grade < stats.lowestGrade)  stats.lowestGrade = grade;
}

// Helper: returns category success percentage, or -1 if no attempts yet
static double categoryPct(int correct, int total)
{
    if (total == 0) return -1.0;
    return (double)correct / total * 100.0;
}

// Displays the logged-in user's personal stats plus a leaderboard across all accounts
void showStatistics(UserAccount accounts[], int accountCount, const string& currentUser)
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("STATISTICS");

    // Locate the current user's account
    int userIdx = findUserIndex(accounts, accountCount, currentUser);

    if (userIdx == -1 || accounts[userIdx].personalStats.totalTests == 0)
    {
        printCenteredText("You have not completed any tests yet.");
        cout << "\n";
        waitForEnter();
        return;
    }

    StatisticsData& s = accounts[userIdx].personalStats;
    double avgGrade = s.sumOfGrades / s.totalTests;
    double htmlPct = categoryPct(s.htmlCorrect, s.htmlTotal);
    double cssPct = categoryPct(s.cssCorrect, s.cssTotal);
    double jsPct = categoryPct(s.jsCorrect, s.jsTotal);

    // ── Personal stats ────────────────────────────────────────────────────────
    printSectionTitle("Your Stats  [ " + currentUser + " ]");
    printLabelValue("Total tests     ", to_string(s.totalTests));
    printLabelValue("Highest grade   ", to_string(s.highestGrade).substr(0, 4));
    printLabelValue("Lowest grade    ", to_string(s.lowestGrade).substr(0, 4));
    printLabelValue("Average grade   ", to_string(avgGrade).substr(0, 4));

    printSectionTitle("Category Performance");
    printLabelValue("HTML      ", htmlPct >= 0 ? to_string((int)htmlPct) + "%" : "no attempts");
    printLabelValue("CSS       ", cssPct >= 0 ? to_string((int)cssPct) + "%" : "no attempts");
    printLabelValue("JavaScript", jsPct >= 0 ? to_string((int)jsPct) + "%" : "no attempts");

    // ── Leaderboard (all active accounts that have taken at least one test) ───
    string topScorer = "", bestHtmlUser = "", bestCssUser = "", bestJsUser = "";
    double topAvg = -1.0, topHtml = -1.0, topCss = -1.0, topJs = -1.0;

    for (int i = 0; i < accountCount; i++)
    {
        if (!accounts[i].used) continue;
        StatisticsData& u = accounts[i].personalStats;
        if (u.totalTests == 0) continue;

        double avg = u.sumOfGrades / u.totalTests;
        if (avg > topAvg) { topAvg = avg; topScorer = accounts[i].username; }

        double hp = categoryPct(u.htmlCorrect, u.htmlTotal);
        double cp = categoryPct(u.cssCorrect, u.cssTotal);
        double jp = categoryPct(u.jsCorrect, u.jsTotal);

        if (hp > topHtml) { topHtml = hp; bestHtmlUser = accounts[i].username; }
        if (cp > topCss) { topCss = cp; bestCssUser = accounts[i].username; }
        if (jp > topJs) { topJs = jp; bestJsUser = accounts[i].username; }
    }

    if (topScorer != "")
    {
        printSectionTitle("Leaderboard");
        printLabelValue("Top scorer      ", topScorer + "  (avg " + to_string(topAvg).substr(0, 4) + ")");
        if (bestHtmlUser != "") printLabelValue("Best HTML       ", bestHtmlUser + "  (" + to_string((int)topHtml) + "%)");
        if (bestCssUser != "") printLabelValue("Best CSS        ", bestCssUser + "  (" + to_string((int)topCss) + "%)");
        if (bestJsUser != "") printLabelValue("Best JavaScript ", bestJsUser + "  (" + to_string((int)topJs) + "%)");
    }

    cout << "\n";
    waitForEnter();
}