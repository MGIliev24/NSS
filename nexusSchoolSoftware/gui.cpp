#include "gui.h"
#include "colors.h"
#include "randomizer.h"
#include "auth.h"
#include "test.h"
#include "statistics.h"
#include "homework.h"
#include <algorithm>
#include <cmath>
#include <cstring>

void Spark(App& a, float x, float y, Color c, int n) {
    for (int i = 0; i < n; i++) {
        float ang = (float)(rand() % 360) * DEG2RAD;
        float sp = 1.f + (rand() % 300) / 100.f;
        Particle p; p.x = x; p.y = y; p.vx = cosf(ang) * sp; p.vy = sinf(ang) * sp;
        p.maxLife = p.life = 0.5f + rand() % 50 / 100.f; p.sz = 2.f + rand() % 4; p.col = c;
        a.parts.push_back(p);
    }
}

void Flash(App& a, const string& m, Color c) {
    a.flashMsg = m; a.flashT = 2.5f; a.flashCol = c;
}

static void TickParticles(App& a, float dt) {
    for (auto& p : a.parts) { p.x += p.vx; p.y += p.vy; p.vy += 0.06f; p.life -= dt; }
    a.parts.erase(remove_if(a.parts.begin(), a.parts.end(), [](const Particle& p) {return p.life <= 0; }), a.parts.end());
}

static void DrawParticles(const App& a) {
    for (auto& p : a.parts) {
        float al = p.life / p.maxLife;
        Color c = { p.col.r,p.col.g,p.col.b,(unsigned char)(al * 200) };
        DrawCircleV({ p.x,p.y }, p.sz * al, c);
    }
}

void InputBox(const char* label, char* buf, int bsz, bool active, bool mask, float x, float y, float w, float h) {
    DrawRectangleRounded({ x,y,w,h }, 0.2f, 8, C_PANEL2);
    DrawRectangleRoundedLinesEx({ x,y,w,h }, 0.2f, 8, active ? 2.f : 1.f, active ? C_ACCENT : Color{ 55,60,110,255 });
    DrawText(label, (int)x, (int)(y - 22), 15, C_DIM);
    string disp; if (mask) disp = string(strlen(buf), '*'); else disp = buf;
    if (active && ((int)(GetTime() * 2) % 2 == 0)) disp += '|';
    DrawText(disp.c_str(), (int)(x + 12), (int)(y + (h - 18) / 2), 18, C_TEXT);
}

void TypeIn(char* buf, int bsz) {
    int len = (int)strlen(buf);
    int k = GetCharPressed();
    while (k > 0) { if (k >= 32 && k < 127 && len < bsz - 2) { buf[len++] = k; buf[len] = 0; }k = GetCharPressed(); }
    if (IsKeyPressed(KEY_BACKSPACE) && len > 0) buf[--len] = 0;
}

void DrawMain(App& a) {
    DrawNSSTitle(a.t);
    DrawHDivider(142);

    string badge = "  " + a.user + "  ";
    int bw = MeasureText(badge.c_str(), 16) + 4;
    DrawRectangleRounded({ (float)(SW - bw - 16),14,(float)(bw + 8),30 }, 0.5f, 8, C_PANEL2);
    DrawText(badge.c_str(), SW - bw - 12, 20, 16, C_MINT);

    struct MI { const char* name, * sub; Color col; };
    MI items[] = {
        {"  Lessons",        "HTML, CSS & JavaScript",      C_ACCENT},
        {"  Take IT Test",   "20 randomized questions",     C_MINT},
        {"  Statistics",     "Your performance & ranking",  C_GOLD},
        {"  Homework",       "Assignments & progress",      C_ROSE},
        {"  Log Out",        "",                            C_DIM},
    };
    float cw = 700, cx = (SW - cw) / 2.f, cy = 172, ch = 72, gap = 10;
    for (int i = 0; i < 5; i++) {
        float y = cy + i * (ch + gap);
        bool hov = CheckCollisionPointRec(GetMousePosition(), { cx,y,cw,ch });
        DrawRectangleRounded({ cx,y,cw,ch }, 0.18f, 8, hov ? C_PANEL2 : C_PANEL);
        DrawRectangleRounded({ cx,y,5,ch }, 0.5f, 4, items[i].col);
        if (hov) DrawRectangleRoundedLinesEx({ cx - 1,y - 1,cw + 2,ch + 2 }, 0.18f, 8, 2.f, items[i].col);
        DrawText(items[i].name, (int)(cx + 18), (int)(y + 14), 24, C_TEXT);
        if (strlen(items[i].sub)) DrawText(items[i].sub, (int)(cx + 18), (int)(y + 46), 14, C_DIM);
        if (hov) DrawText(">", (int)(cx + cw - 26), (int)(y + 22), 22, items[i].col);
        if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (i == 0) a.scr = SCR_LESSONS;
            else if (i == 1) {
                bool used[30] = {};
                int cur = 0, needs[3] = { 7,7,6 }, lo[3] = { 0,10,20 }, hi[3] = { 9,19,29 };
                for (int c = 0; c < 3; c++) while (needs[c] > 0) { int idx = getRandomInt(lo[c], hi[c]); if (!used[idx]) { used[idx] = true; a.sel[cur++] = idx; needs[c]--; } }
                for (int ii = 0; ii < 19; ii++) { int jj = getRandomInt(ii, 19); int tmp = a.sel[ii]; a.sel[ii] = a.sel[jj]; a.sel[jj] = tmp; }
                a.tCur = 0; a.tOk = 0; a.tAns = -1; a.tDone = false; a.scr = SCR_TEST;
            }
            else if (i == 2) a.scr = SCR_STATS;
            else if (i == 3) a.scr = SCR_HW;
            else if (i == 4) {
                Flash(a, "Goodbye, " + a.user + "!", C_MINT);
                a.user = ""; a.userIdx = -1; a.isLogin = true; a.scr = SCR_AUTH;
            }
        }
    }
}

void DrawLessons(App& a) {
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered("LESSON MODULES", 160, 30, C_ACCENT);
    struct LI { const char* name, * desc; Color col; Screen dest; };
    LI items[] = {
        {"HTML Basics",       "Tags, structure, elements",     C_ROSE,  SCR_LESSON_HTML},
        {"CSS Basics",        "Selectors, properties, layout", C_ACCENT,SCR_LESSON_CSS},
        {"JavaScript Basics", "Logic, loops, events",          C_GOLD,  SCR_LESSON_JS},
        {"<- Back",           "",                              C_DIM,   SCR_MAIN},
    };
    float cx = (SW - 700) / 2.f, cy = 210;
    for (int i = 0; i < 4; i++) {
        bool hov = CheckCollisionPointRec(GetMousePosition(), { cx,cy,700,72 });
        DrawRectangleRounded({ cx,cy,700,72 }, 0.18f, 8, hov ? C_PANEL2 : C_PANEL);
        DrawRectangleRounded({ cx,cy,5,72 }, 0.5f, 4, items[i].col);
        if (hov) DrawRectangleRoundedLinesEx({ cx - 1,cy - 1,702,74 }, 0.18f, 8, 2.f, items[i].col);
        DrawText(items[i].name, (int)(cx + 18), (int)(cy + 16), 22, C_TEXT);
        if (strlen(items[i].desc)) DrawText(items[i].desc, (int)(cx + 18), (int)(cy + 46), 14, C_DIM);
        if (hov) DrawText(">", (int)(cx + 674), (int)(cy + 22), 20, items[i].col);
        if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) a.scr = items[i].dest;
        cy += 84;
    }
}

void DrawLesson(App& a, const char* title, const char* sub, const vector<LessonItem>& items, Color ac) {
    DrawNSSTitle(a.t); DrawHDivider(142);
    DrawCentered(title, 158, 32, ac);
    DrawCentered(sub, 200, 15, C_DIM);

    static float scrollY = 0;
    scrollY += GetMouseWheelMove() * 40.0f;
    if (scrollY > 0) scrollY = 0;

    BeginScissorMode(0, 230, SW, SH - 230);
    float tx = 120, tw = 860, ty = 232 + scrollY;

    DrawRectangleRounded({ tx,ty,(float)tw,26 }, 0.2f, 4, C_PANEL2);
    DrawText("ELEMENT / PROPERTY", (int)(tx + 16), (int)(ty + 5), 14, C_DIM);
    DrawText("DESCRIPTION", (int)(tx + 320), (int)(ty + 5), 14, C_DIM);
    ty += 30;

    for (auto& it : items) {
        bool hov = CheckCollisionPointRec(GetMousePosition(), { tx,ty,(float)tw,42 });
        DrawRectangleRounded({ tx,ty,(float)tw,42 }, 0.12f, 4, hov ? C_PANEL2 : C_PANEL);
        DrawText(it.tag.c_str(), (int)(tx + 16), (int)(ty + 11), 17, ac);
        DrawText(it.desc.c_str(), (int)(tx + 320), (int)(ty + 11), 17, C_TEXT);
        ty += 46;
    }

    if (UIButton("<- Back to Lessons", tx, ty + 14, 210, 42, C_PANEL2, C_DIM, 16)) {
        scrollY = 0;
        a.scr = SCR_LESSONS;
    }
    EndScissorMode();
}

void DrawAppScreen(App& a) {
    float dt = GetFrameTime();
    a.t += dt;

    if (a.flashT > 0) a.flashT -= dt;
    a.partTimer -= dt;
    if (a.partTimer < 0) { a.partTimer = 4.f; Spark(a, (float)(rand() % SW), (float)(SH + 5), { 50,70,150,150 }, 2); }
    TickParticles(a, dt);

    for (int gx = 0; gx < SW; gx += 80) DrawLine(gx, 0, gx, SH, { 28,32,65,28 });
    for (int gy = 0; gy < SH; gy += 80) DrawLine(0, gy, SW, gy, { 28,32,65,28 });
    DrawParticles(a);

    switch (a.scr) {
    case SCR_AUTH:        DrawAuth(a);   break;
    case SCR_MAIN:        DrawMain(a);   break;
    case SCR_LESSONS:     DrawLessons(a); break;
    case SCR_LESSON_HTML: DrawLesson(a, "HTML BASICS", "HyperText Markup Language - structures web pages.", getHtmlItems(), C_ROSE); break;
    case SCR_LESSON_CSS:  DrawLesson(a, "CSS BASICS", "Cascading Style Sheets - controls visual style.", getCssItems(), C_ACCENT);   break;
    case SCR_LESSON_JS:   DrawLesson(a, "JAVASCRIPT BASICS", "Adds logic and interactivity to web pages.", getJsItems(), C_GOLD);    break;
    case SCR_TEST:        DrawTest(a);   break;
    case SCR_STATS:       DrawStats(a);  break;
    case SCR_HW:          DrawHomework(a);  break;
    case SCR_HW_DETAIL:   DrawHWDetail(a);  break;
    case SCR_HW_TEST:     DrawHWTest(a);    break;
    default: break;
    }

    if (a.flashT > 0) {
        float al = min(1.f, a.flashT) * 255;
        int fw = MeasureText(a.flashMsg.c_str(), 17) + 40;
        DrawRectangleRounded({ (float)(SW / 2 - fw / 2),(float)(SH - 68),(float)fw,38 }, 0.5f, 8,
            { a.flashCol.r,a.flashCol.g,a.flashCol.b,(unsigned char)min(220.f,al) });
        DrawText(a.flashMsg.c_str(), SW / 2 - MeasureText(a.flashMsg.c_str(), 17) / 2, (int)(SH - 60), 17,
            { 255,255,255,(unsigned char)min(220.f,al) });
    }
}