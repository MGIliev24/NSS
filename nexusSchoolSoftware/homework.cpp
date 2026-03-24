#include "homework.h"
#include "gui.h"
#include "colors.h"
#include "auth.h"
#include <string>

void initializeHomeworkAssignments(HomeworkAssignment a[]) {
    a[0].title = "HTML Fundamentals"; a[0].description = "Practice HTML tags and page structure.";
    a[1].title = "CSS Styling";        a[1].description = "Practice CSS properties and selectors.";
    a[2].title = "JavaScript Basics";  a[2].description = "Practice JavaScript fundamentals.";
    for (int i = 0; i < hwQuestionCount; i++) {
        a[0].questionIndexes[i] = i;
        a[1].questionIndexes[i] = i + 10;
        a[2].questionIndexes[i] = i + 20;
    }
}

void DrawHomework(App& a) {
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered("HOMEWORK", 160, 30, C_ROSE);
    float cx = (SW - 700) / 2.f, cy = 210;
    for (int i = 0; i < homeworkCount; i++) {
        auto& rec = a.accounts[a.userIdx].homeworkRecords[i];
        bool hov = CheckCollisionPointRec(GetMousePosition(), { cx,cy,700,80 });
        DrawRectangleRounded({ cx,cy,700,80 }, 0.14f, 8, hov ? C_PANEL2 : C_PANEL);
        DrawRectangleRounded({ cx,cy,5,80 }, 0.5f, 4, C_ROSE);
        if (hov) DrawRectangleRoundedLinesEx({ cx - 1,cy - 1,702,82 }, 0.14f, 8, 2.f, C_ROSE);

        Color sc; const char* st2;
        if (rec.status == DONE) { sc = C_GREEN; st2 = "DONE"; }
        else if (rec.status == VIEWED) { sc = C_GOLD; st2 = "VIEWED"; }
        else { sc = C_RED; st2 = "UNDONE"; }
        int sbw = MeasureText(st2, 13) + 16;
        DrawRectangleRounded({ cx + 700 - sbw - 10,cy + 12,(float)sbw,24 }, 0.5f, 4, sc);
        DrawText(st2, (int)(cx + 700 - sbw - 2), (int)(cy + 17), 13, C_BG);
        DrawText(a.hw[i].title.c_str(), (int)(cx + 18), (int)(cy + 14), 22, C_TEXT);
        DrawText(a.hw[i].description.c_str(), (int)(cx + 18), (int)(cy + 46), 14, C_DIM);
        if (rec.status == DONE) {
            string sc2 = to_string(rec.score) + "/" + to_string(hwQuestionCount);
            DrawText(sc2.c_str(), (int)(cx + 18), (int)(cy + 58), 13, C_GREEN);
        }
        if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            a.hwSel = i;
            if (rec.status == UNDONE) rec.status = VIEWED;
            a.scr = SCR_HW_DETAIL;
        }
        cy += 92;
    }
    if (UIButton("<- Main Menu", (float)(SW / 2 - 90), cy + 10, 180, 44, C_PANEL2, C_DIM, 17)) a.scr = SCR_MAIN;
}

void DrawHWDetail(App& a) {
    int i = a.hwSel;
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered(a.hw[i].title.c_str(), 160, 28, C_ROSE);
    DrawCard((SW - 600) / 2.f, 205, 600, 200, 0.1f);
    float dx = (SW - 600) / 2.f + 28; float dy = 224;
    DrawText(a.hw[i].description.c_str(), (int)dx, (int)dy, 17, C_TEXT); dy += 42;
    auto& rec = a.accounts[a.userIdx].homeworkRecords[i];
    string stS; Color stC;
    if (rec.status == DONE) { stS = "Done - " + to_string(rec.score) + "/" + to_string(hwQuestionCount); stC = C_GREEN; }
    else if (rec.status == VIEWED) { stS = "Viewed - not submitted"; stC = C_GOLD; }
    else { stS = "Not started"; stC = C_RED; }
    DrawText("Status:", (int)dx, (int)dy, 16, C_DIM);
    DrawText(stS.c_str(), (int)(dx + 80), (int)dy, 16, stC); dy += 36;
    if (rec.status == DONE) DrawProgressBar(dx, dy, 540, 12, (float)rec.score / hwQuestionCount, C_GREEN);
    float bx = (SW - 420) / 2.f, by = 430;
    const char* sl = rec.status == DONE ? "Redo Homework" : "Start Homework";
    if (UIButton(sl, bx, by, 200, 44, C_ACCENT, WHITE, 17)) {
        a.hwCur = 0; a.hwOk = 0; a.hwAns = -1; a.hwDone = false; a.scr = SCR_HW_TEST;
    }
    if (UIButton("<- Back", bx + 220, by, 200, 44, C_PANEL2, C_DIM, 17)) a.scr = SCR_HW;
}

void DrawHWTest(App& a) {
    int i = a.hwSel;
    if (a.hwDone) {
        DrawNSSTitle(a.t); DrawHDivider(142);
        DrawCentered("HOMEWORK RESULT", 160, 28, C_ROSE);
        DrawCard(SW / 2.f - 210, 210, 420, 200, 0.1f);
        string sc = to_string(a.hwOk) + "/" + to_string(hwQuestionCount);
        double pct = (double)a.hwOk / hwQuestionCount * 100;
        DrawCentered(sc.c_str(), 244, 34, C_TEXT);
        DrawCentered((to_string((int)pct) + "%").c_str(), 292, 26, pct >= 70 ? C_GREEN : pct >= 50 ? C_GOLD : C_RED);
        DrawProgressBar(SW / 2.f - 150, 346, 300, 12, (float)a.hwOk / hwQuestionCount, C_GREEN);
        if (UIButton("<- Homework", (float)(SW / 2 - 85), 380, 170, 44, C_PANEL2, C_DIM, 17)) a.scr = SCR_HW;
        return;
    }
    Question& q = a.qbank[a.hw[i].questionIndexes[a.hwCur]];
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered(a.hw[i].title.c_str(), 160, 24, C_ROSE);
    DrawProgressBar(80, 194, SW - 160, 10, (float)a.hwCur / hwQuestionCount, C_ROSE);
    string prog = "Q " + to_string(a.hwCur + 1) + "/" + to_string(hwQuestionCount);
    DrawCentered(prog.c_str(), 210, 13, C_DIM);
    DrawCard(120, 232, SW - 240, 82, 0.1f);
    DrawCentered(q.text.c_str(), 258, 18, C_TEXT);
    const char* opts[] = { q.optionA.c_str(),q.optionB.c_str(),q.optionC.c_str() };
    const char* labs[] = { "A","B","C" };
    float oy = 328, ow = 700, ox = (SW - ow) / 2.f;
    for (int ii = 0; ii < 3; ii++) {
        bool ans = a.hwAns != -1;
        bool corr = (char)('A' + ii) == q.correctAnswer, chose = a.hwAns == ii;
        Color bg = C_PANEL, brd = C_PANEL;
        if (ans) { if (corr) { bg = { 20,60,30,255 }; brd = C_GREEN; } else if (chose) { bg = { 60,20,25,255 }; brd = C_RED; } }
        else { bool hov = CheckCollisionPointRec(GetMousePosition(), { ox,oy,ow,52 }); if (hov) { bg = C_PANEL2; brd = C_ROSE; } }
        DrawRectangleRounded({ ox,oy,ow,52 }, 0.14f, 8, bg);
        DrawRectangleRoundedLinesEx({ ox,oy,ow,52 }, 0.14f, 8, 1.5f, brd);
        DrawRectangleRounded({ ox + 12,oy + 13,28,26 }, 0.5f, 4, { 55,60,120,200 });
        DrawText(labs[ii], (int)(ox + 20), (int)(oy + 17), 16, C_ROSE);
        DrawText(opts[ii], (int)(ox + 52), (int)(oy + 16), 17, C_TEXT);
        if (!ans && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), { ox,oy,ow,52 })) {
            a.hwAns = ii;
            if ((char)('A' + ii) == q.correctAnswer) { a.hwOk++; Spark(a, ox + ow / 2, oy + 26, C_GREEN, 20); }
            else Spark(a, ox + ow / 2, oy + 26, C_RED, 10);
        }
        oy += 60;
    }
    if (a.hwAns != -1) {
        bool last = a.hwCur == hwQuestionCount - 1;
        if (UIButton(last ? "See Results ->" : "Next ->", (float)(SW / 2 - 85), oy + 10, 170, 44, C_ROSE, WHITE, 18)) {
            if (last) {
                a.accounts[a.userIdx].homeworkRecords[i].score = a.hwOk;
                a.accounts[a.userIdx].homeworkRecords[i].status = DONE;
                a.hwDone = true; Spark(a, SW / 2.f, SH / 2.f, C_ROSE, 40);
            }
            else { a.hwCur++; a.hwAns = -1; }
        }
    }
}