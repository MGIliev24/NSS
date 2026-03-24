#pragma once
#include "raylib.h"
#include "auth.h"
#include "homework.h"
#include "question.h"
#include "test.h"
#include <string>
#include <vector>

using namespace std;

enum Screen {
    SCR_AUTH, SCR_MAIN, SCR_LESSONS,
    SCR_LESSON_HTML, SCR_LESSON_CSS, SCR_LESSON_JS,
    SCR_TEST, SCR_TEST_RESULT,
    SCR_STATS,
    SCR_HW, SCR_HW_DETAIL, SCR_HW_TEST, SCR_HW_RESULT
};

struct Particle {
    float x, y, vx, vy, life, maxLife, sz;
    Color col;
};

struct App {
    UserAccount         accounts[maxAccounts];
    HomeworkAssignment  hw[homeworkCount];
    Question            qbank[questionBankSize];

    string  user;
    int     userIdx = -1;
    Screen  scr = SCR_AUTH;
    float   t = 0;

    char  uBuf[64] = {}, pBuf[64] = {};
    bool  uActive = false, pActive = false;
    bool  isLogin = true, showPw = false;
    string authMsg;

    int  sel[testQuestionCount];
    int  tCur = 0, tOk = 0, tAns = -1;
    bool tDone = false;
    double tGrade = 2.0;

    int  hwSel = -1, hwCur = 0, hwOk = 0, hwAns = -1;
    bool hwDone = false;

    vector<Particle> parts;
    float partTimer = 0;

    string flashMsg;
    float flashT = 0;
    Color flashCol;
};

// Global UI Helpers
void Spark(App& a, float x, float y, Color c, int n = 14);
void Flash(App& a, const string& m, Color c = { 80, 220, 140, 255 }); // Default Green
void InputBox(const char* label, char* buf, int bsz, bool active, bool mask, float x, float y, float w, float h);
void TypeIn(char* buf, int bsz);

// Core Main Screens handled in gui.cpp
void DrawMain(App& a);
void DrawLessons(App& a);
void DrawLesson(App& a, const char* title, const char* sub, const vector<LessonItem>& items, Color ac);

// The main dispatcher
void DrawAppScreen(App& a);