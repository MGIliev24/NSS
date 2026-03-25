#include "statistics.h"
#include "gui.h"
#include "colors.h"
#include "auth.h"
#include <algorithm>
#include <string>

// Initializes statistics data
void initializeStatistics(StatisticsData& s) {
    s.totalTests = 0; s.highestGrade = 2.0; s.lowestGrade = 6.0; s.sumOfGrades = 0.0;
    s.htmlCorrect = s.htmlTotal = s.cssCorrect = s.cssTotal = s.jsCorrect = s.jsTotal = 0;
}
//test statistics with a new grade

void updateOverallStatistics(StatisticsData& s, double grade) {
    s.totalTests++;
    s.sumOfGrades += grade;
    if (grade > s.highestGrade) s.highestGrade = grade;
    if (grade < s.lowestGrade)  s.lowestGrade = grade;
}
//dashboard with user performance

void DrawStats(App& a) {
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered("STATISTICS", 160, 30, C_GOLD);
    if (a.userIdx < 0 || a.accounts[a.userIdx].personalStats.totalTests == 0) {
        DrawCentered("No tests completed yet.", 300, 20, C_DIM);
        if (UIButton("<- Back", (float)(SW / 2 - 80), 360, 160, 44, C_PANEL2, C_DIM, 17)) a.scr = SCR_MAIN;
        return;
    }
    auto& st = a.accounts[a.userIdx].personalStats;
    double avg = st.sumOfGrades / st.totalTests;
    float hw2 = (SW - 240) / 2.f;

    DrawCard(100, 202, hw2, 260, 0.08f);
    DrawText(("  " + a.user).c_str(), (int)(114), (int)(218), 20, C_MINT);
    DrawHDivider(244, 100);
    float ry = 252; float rx = 114;
    auto Row = [&](const char* lbl, const char* val, Color vc) {
        DrawText(lbl, (int)rx, (int)ry, 16, C_DIM);
        DrawText(val, (int)(rx + 220), (int)ry, 16, vc); ry += 32;
        };
    Row("Total Tests", to_string(st.totalTests).c_str(), C_TEXT);
    Row("Highest", (to_string(st.highestGrade).substr(0, 4) + "/6").c_str(), C_GREEN);
    Row("Lowest", (to_string(st.lowestGrade).substr(0, 4) + "/6").c_str(), C_RED);
    Row("Average", (to_string(avg).substr(0, 4) + "/6").c_str(), C_GOLD);

    struct CB { const char* n; int c, tot; Color col; };
    CB cats[] = { {"HTML",st.htmlCorrect,st.htmlTotal,C_ROSE},
               {"CSS", st.cssCorrect, st.cssTotal, C_ACCENT},
               {"JS",  st.jsCorrect,  st.jsTotal,  C_GOLD} };
    ry += 4;
    for (auto& cb : cats) {
        DrawText(cb.n, (int)rx, (int)ry, 14, cb.col);
        float pct = cb.tot > 0 ? (float)cb.c / cb.tot : 0;
        DrawProgressBar(rx + 42, ry + 2, hw2 - 90, 12, pct, cb.col);
        string ps = cb.tot > 0 ? to_string((int)(pct * 100)) + "%" : "N/A";
        DrawText(ps.c_str(), (int)(rx + hw2 - 52), (int)ry, 13, C_DIM);
        ry += 24;
    }

    float lx = 100 + hw2 + 40;
    DrawCard(lx, 202, hw2, 260, 0.08f);
    DrawText("  LEADERBOARD", (int)(lx + 16), (int)(218), 20, C_GOLD);
    DrawHDivider(244, lx);
    vector<pair<double, string>> board;
    for (int i = 0; i < maxAccounts; i++)
        if (a.accounts[i].used && a.accounts[i].personalStats.totalTests > 0)
            board.push_back({ a.accounts[i].personalStats.sumOfGrades / a.accounts[i].personalStats.totalTests,a.accounts[i].username });
    sort(board.rbegin(), board.rend());
    float ly = 252;
    Color mCols[] = { C_GOLD,{192,192,192,255},{180,110,0,255} };
    for (int i = 0; i < (int)board.size() && i < 8; i++) {
        bool me = board[i].second == a.user;
        if (me) DrawRectangleRounded({ lx + 8,ly,(float)(hw2 - 16),28 }, 0.2f, 4, { 30,40,70,200 });
        Color tc = i < 3 ? mCols[i] : (me ? C_MINT : C_DIM);
        string rank = to_string(i + 1) + ".  " + board[i].second;
        DrawText(rank.c_str(), (int)(lx + 18), (int)(ly + 6), 15, tc);
        string av2 = to_string(board[i].first).substr(0, 4);
        DrawText(av2.c_str(), (int)(lx + hw2 - 52), (int)(ly + 6), 15, tc);
        ly += 32;
    }
    if (UIButton("<- Main Menu", (float)(SW / 2 - 90), 480, 180, 44, C_PANEL2, C_DIM, 17)) a.scr = SCR_MAIN;
}