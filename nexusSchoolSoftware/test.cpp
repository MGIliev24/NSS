#include "test.h"
#include "gui.h"
#include "colors.h"
#include <string>

void DrawTest(App& a) {
    if (a.tDone) {
        DrawNSSTitle(a.t); DrawHDivider(142);
        DrawCentered("TEST RESULT", 162, 34, C_GOLD);
        DrawCard(SW / 2.f - 240, 210, 480, 220, 0.1f);
        string sc = to_string(a.tOk) + "/20  (" + to_string((int)((double)a.tOk / 20 * 100)) + "%)";
        string gr = "Grade: " + to_string((int)a.tGrade) + " / 6";
        Color gc = a.tGrade >= 5 ? C_GREEN : a.tGrade >= 3 ? C_GOLD : C_RED;
        DrawCentered(sc.c_str(), 240, 26, C_TEXT);
        DrawCentered(gr.c_str(), 290, 32, gc);
        DrawProgressBar(SW / 2.f - 160, 348, 320, 16, (float)a.tOk / 20.f, gc);
        if (UIButton("Main Menu", (float)(SW / 2 - 90), 400, 180, 44, C_ACCENT, WHITE, 18)) a.scr = SCR_MAIN;
        return;
    }
    Question& q = a.qbank[a.sel[a.tCur]];
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered("IT TEST", 160, 28, C_ACCENT);
    DrawProgressBar(80, 196, SW - 160, 10, (float)a.tCur / 20.f, C_ACCENT);
    string prog = "Question " + to_string(a.tCur + 1) + " of 20  |  Correct: " + to_string(a.tOk);
    DrawCentered(prog.c_str(), 212, 14, C_DIM);

    const char* cn[] = { "HTML","CSS","JavaScript" }; Color cc[] = { C_ROSE,C_ACCENT,C_GOLD };
    int cat = q.category; int cbw = MeasureText(cn[cat], 14) + 20;
    DrawRectangleRounded({ (float)(SW / 2 - cbw / 2),232,(float)cbw,26 }, 0.5f, 8, cc[cat]);
    DrawText(cn[cat], SW / 2 - MeasureText(cn[cat], 14) / 2, 238, 14, C_BG);

    DrawCard(120, 268, SW - 240, 84, 0.1f);
    DrawCentered(q.text.c_str(), 292, 19, C_TEXT);

    const char* opts[] = { q.optionA.c_str(),q.optionB.c_str(),q.optionC.c_str() };
    const char* labs[] = { "A","B","C" };
    float oy = 366, ow = 700, ox = (SW - ow) / 2.f;
    for (int i = 0; i < 3; i++) {
        bool ans = a.tAns != -1;
        bool corr = (char)('A' + i) == q.correctAnswer, chose = a.tAns == i;
        Color bg = C_PANEL, brd = C_PANEL;
        if (ans) { if (corr) { bg = { 20,60,30,255 }; brd = C_GREEN; } else if (chose) { bg = { 60,20,25,255 }; brd = C_RED; } }
        else { bool hov = CheckCollisionPointRec(GetMousePosition(), { ox,oy,ow,52 }); if (hov) { bg = C_PANEL2; brd = C_ACCENT; } }
        DrawRectangleRounded({ ox,oy,ow,52 }, 0.14f, 8, bg);
        DrawRectangleRoundedLinesEx({ ox,oy,ow,52 }, 0.14f, 8, 1.5f, brd);
        DrawRectangleRounded({ ox + 12,oy + 13,28,26 }, 0.5f, 4, { 55,60,120,200 });
        DrawText(labs[i], (int)(ox + 20), (int)(oy + 17), 16, C_ACCENT);
        DrawText(opts[i], (int)(ox + 52), (int)(oy + 16), 17, C_TEXT);
        if (!ans && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), { ox,oy,ow,52 })) {
            a.tAns = i;
            if ((char)('A' + i) == q.correctAnswer) { a.tOk++; Spark(a, ox + ow / 2, oy + 26, C_GREEN, 20); }
            else Spark(a, ox + ow / 2, oy + 26, C_RED, 10);
            if (a.userIdx >= 0) {
                auto& st = a.accounts[a.userIdx].personalStats;
                if (cat == 0) { st.htmlTotal++; if ((char)('A' + i) == q.correctAnswer)st.htmlCorrect++; }
                else if (cat == 1) { st.cssTotal++; if ((char)('A' + i) == q.correctAnswer)st.cssCorrect++; }
                else { st.jsTotal++; if ((char)('A' + i) == q.correctAnswer)st.jsCorrect++; }
            }
        }
        oy += 60;
    }
    if (a.tAns != -1) {
        bool last = a.tCur == 19;
        if (UIButton(last ? "See Results ->" : "Next ->", (float)(SW / 2 - 85), oy + 10, 170, 44, C_ACCENT, WHITE, 18)) {
            if (last) {
                double pct = (double)a.tOk / 20;
                a.tGrade = 2.0;
                if (pct >= 0.9)a.tGrade = 6; else if (pct >= 0.75)a.tGrade = 5;
                else if (pct >= 0.6)a.tGrade = 4; else if (pct >= 0.45)a.tGrade = 3;
                if (a.userIdx >= 0) updateOverallStatistics(a.accounts[a.userIdx].personalStats, a.tGrade);
                a.tDone = true; Spark(a, SW / 2.f, SH / 2.f, C_GOLD, 40);
            }
            else { a.tCur++; a.tAns = -1; }
        }
    }
}