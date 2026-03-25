#include "auth.h"
#include "gui.h"
#include "colors.h"
#include <cstring>
#include <cmath>
#include <cstdlib>

// //Initializes all account slots with default values

void initializeAccounts(UserAccount accounts[], int size) {
    for (int i = 0; i < size; i++) {
        accounts[i].username = ""; accounts[i].password = ""; accounts[i].used = false;
        initializeStatistics(accounts[i].personalStats);
        for (int h = 0; h < homeworkCount; h++) {
            accounts[i].homeworkRecords[h].status = UNDONE;
            accounts[i].homeworkRecords[h].score = 0;
        }
    }
}

// Searches for an active user and returns its array index, or -1 if not found

int findUserIndex(UserAccount accounts[], int size, const string& username) {
    for (int i = 0; i < size; i++)
        if (accounts[i].used && accounts[i].username == username) return i;
    return -1;
}
// Renders the authentication screen

void DrawAuth(App& a) {
    srand(42);
    // Draw animated background

    for (int i = 0; i < 80; i++) {
        float bri = 0.3f + 0.7f * sinf(a.t * 0.6f + i);
        DrawCircle(rand() % SW, rand() % SH, 1, { (unsigned char)(bri * 180),(unsigned char)(bri * 190),255,80 });
    }
    DrawNSSTitle(a.t);

    float cx = (SW - 400) / 2.f, cy = 155.f;

    DrawCard(cx, cy, 400, 410, 0.08f);

    bool h1 = CheckCollisionPointRec(GetMousePosition(), { cx,cy,200,44 });
    bool h2 = CheckCollisionPointRec(GetMousePosition(), { cx + 200,cy,200,44 });
    DrawRectangleRounded({ cx,cy,200,44 }, 0.35f, 8, a.isLogin ? C_ACCENT : C_PANEL2);
    DrawRectangleRounded({ cx + 200,cy,200,44 }, 0.35f, 8, !a.isLogin ? C_ACCENT : C_PANEL2);
    int lw = MeasureText("Log In", 18), sw2 = MeasureText("Sign Up", 18);
    DrawText("Log In", (int)(cx + (200 - lw) / 2), (int)(cy + 13), 18, a.isLogin ? WHITE : C_DIM);
    DrawText("Sign Up", (int)(cx + 200 + (200 - sw2) / 2), (int)(cy + 13), 18, !a.isLogin ? WHITE : C_DIM);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (h1) { a.isLogin = true; a.authMsg = ""; }
        if (h2) { a.isLogin = false; a.authMsg = ""; }
    }

    bool cu = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), { cx + 30,cy + 82,340,40 });
    bool cp = IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), { cx + 30,cy + 162,300,40 });
    if (cu) { a.uActive = true; a.pActive = false; }
    if (cp) { a.uActive = false; a.pActive = true; }

    InputBox("Username", a.uBuf, 64, a.uActive, false, cx + 30, cy + 82, 340, 40);
    InputBox("Password", a.pBuf, 64, a.pActive, !a.showPw, cx + 30, cy + 162, 300, 40);

    bool eh = CheckCollisionPointRec(GetMousePosition(), { cx + 338,cy + 162,32,40 });
    DrawRectangleRounded({ cx + 338,cy + 162,32,40 }, 0.2f, 8, C_PANEL2);
    DrawText(a.showPw ? "H" : "S", (int)(cx + 346), (int)(cy + 174), 14, C_DIM);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && eh) a.showPw = !a.showPw;

    if (a.uActive) TypeIn(a.uBuf, 64);
    if (a.pActive) TypeIn(a.pBuf, 64);
    if (IsKeyPressed(KEY_TAB)) { a.uActive = !a.uActive; a.pActive = !a.pActive; }

    bool go = UIButton(a.isLogin ? "LOG IN" : "CREATE ACCOUNT", cx + 30, cy + 230, 340, 46, C_ACCENT, WHITE, 19) ||
        (IsKeyPressed(KEY_ENTER) && (a.uActive || a.pActive));

    if (UIButton("EXIT PROGRAM", cx + 30, cy + 286, 340, 40, C_PANEL2, C_DIM, 17)) {
        exit(0);
    }
    // Handle login and account creation

    if (go) {
        string u = a.uBuf, p = a.pBuf;
        if (u.empty() || p.empty()) { a.authMsg = "Fill in both fields."; }
        else if (a.isLogin) {
            int idx = findUserIndex(a.accounts, maxAccounts, u);
            if (idx < 0) a.authMsg = "User not found.";
            else if (a.accounts[idx].password != p) a.authMsg = "Wrong password.";
            else {
                a.user = u; a.userIdx = idx;
                a.scr = SCR_MAIN; Flash(a, "Welcome back, " + u + "!", C_MINT);
                Spark(a, SW / 2.f, SH / 2.f, C_ACCENT, 30);
                memset(a.uBuf, 0, 64); memset(a.pBuf, 0, 64);
            }
        }
        else {
            bool exists = findUserIndex(a.accounts, maxAccounts, u) >= 0;
            if (exists) { a.authMsg = "Username taken."; }
            else {
                int slot = -1;
                for (int i = 0; i < maxAccounts; i++) if (!a.accounts[i].used) { slot = i; break; }
                if (slot < 0) { a.authMsg = "Server full."; }
                else {
                    a.accounts[slot].username = u; a.accounts[slot].password = p; a.accounts[slot].used = true;
                    a.user = u; a.userIdx = slot;
                    a.scr = SCR_MAIN; Flash(a, "Welcome, " + u + "!", C_MINT);
                    Spark(a, SW / 2.f, SH / 2.f, C_MINT, 30);
                    memset(a.uBuf, 0, 64); memset(a.pBuf, 0, 64);
                }
            }
        }
    }
    if (!a.authMsg.empty()) DrawCentered(a.authMsg.c_str(), cy + 344, 15, C_RED);
}