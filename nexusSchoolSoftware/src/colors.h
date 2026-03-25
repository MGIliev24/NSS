#pragma once
//color definitions and UI drawing

#include "raylib.h"
#include <string>
using namespace std;

static const Color C_BG = { 20,  30,  28, 255 };
static const Color C_PANEL = { 30,  48,  44, 255 };
static const Color C_PANEL2 = { 42,  65,  58, 255 };
static const Color C_ACCENT = { 235, 75,  90, 255 };
static const Color C_MINT = { 110, 205, 160, 255 };
static const Color C_ROSE = { 235, 75,  90, 255 };
static const Color C_GOLD = { 220, 185, 100, 255 }; 
static const Color C_TEXT = { 230, 240, 235, 255 }; 
static const Color C_DIM = { 130, 160, 150, 255 }; 
static const Color C_GREEN = { 110, 205, 160, 255 }; 
static const Color C_RED = { 235, 75,  90, 255 };

static const int SW = 1100;
static const int SH = 720;

inline void DrawCard(float x, float y, float w, float h, float r = 0.08f) {
    
    DrawRectangleRounded({ x,y,w,h }, r, 8, C_PANEL);
    DrawRectangleRoundedLinesEx({ x,y,w,h }, r, 8, 2.f, C_PANEL2);
}
inline void DrawHDivider(float y, float mx = 80.f) {
    DrawLine((int)mx, (int)y, SW - (int)mx, (int)y, C_PANEL2);
}
inline void DrawProgressBar(float x, float y, float w, float h, float pct, Color fill) {
    DrawRectangleRounded({ x,y,w,h }, 0.5f, 6, C_PANEL2);
    if (pct > 0.f) DrawRectangleRounded({ x,y,w * pct,h }, 0.5f, 6, fill);
}
inline void DrawNSSTitle(float t) {
    float pulse = 0.5f + 0.5f * sinf(t * 2.f);
    const char* L1 = "NEXUS"; const char* L2 = "SCHOOL SOFTWARE";
    int w1 = MeasureText(L1, 64), w2 = MeasureText(L2, 26);
    for (int i = 4; i > 0; i--) {
        Color gc = { (unsigned char)(110 + pulse * 30),205,160,(unsigned char)(25 * i) };
        DrawText(L1, (SW - w1) / 2 - i, 30 - i, 64, gc);
    }
    DrawText(L1, (SW - w1) / 2, 30, 64, C_ACCENT);
    Color c2 = { (unsigned char)(150 + pulse * 50),220,180,255 };
    DrawText(L2, (SW - w2) / 2, 100, 26, c2);
}
inline bool UIButton(const char* label, float x, float y, float w, float h,
    Color bg, Color fg, int fs = 18) {
    bool hov = CheckCollisionPointRec(GetMousePosition(), { x,y,w,h });
    Color c = hov ? Color{ (unsigned char)min(255,(int)bg.r + 30),
                      (unsigned char)min(255,(int)bg.g + 30),
                      (unsigned char)min(255,(int)bg.b + 30),bg.a } : bg;
    DrawRectangleRounded({ x,y,w,h }, 0.35f, 8, c);
    if (hov) DrawRectangleRoundedLinesEx({ x - 1,y - 1,w + 2,h + 2 }, 0.35f, 8, 2.f, C_TEXT);
    int tw = MeasureText(label, fs);
    DrawText(label, (int)(x + (w - tw) / 2), (int)(y + (h - fs) / 2), fs, fg);
    return hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
inline void DrawCentered(const char* txt, float y, int fs, Color col) {
    DrawText(txt, (SW - MeasureText(txt, fs)) / 2, (int)y, fs, col);
}