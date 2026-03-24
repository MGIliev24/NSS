#pragma once
#include <string>
#include "question.h"
using namespace std;

const int homeworkCount = 3;
const int hwQuestionCount = 10;

enum HomeworkStatus { UNDONE, VIEWED, DONE };

struct HomeworkRecord {
    HomeworkStatus status = UNDONE;
    int score = 0;
};

struct HomeworkAssignment {
    string title, description;
    int questionIndexes[hwQuestionCount] = {};
};

void initializeHomeworkAssignments(HomeworkAssignment a[]);

struct App;
void DrawHomework(App& a);
void DrawHWDetail(App& a);
void DrawHWTest(App& a);