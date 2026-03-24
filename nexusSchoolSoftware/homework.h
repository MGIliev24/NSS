#ifndef HOMEWORK_H
#define HOMEWORK_H
#include <string>
#include "question.h"
using namespace std;

const int homeworkCount = 3;   // number of homework assignments
const int hwQuestionCount = 10;  // questions per homework

// Three possible states a homework can be in for a given user
enum HomeworkStatus { UNDONE, VIEWED, DONE };

// Stores the result for one homework assignment for one user
struct HomeworkRecord
{
    HomeworkStatus status;
    int score;          // number correct; 0 if not done yet
};

// Describes a single homework assignment (title + which question-bank indexes to use)
struct HomeworkAssignment
{
    string title;
    string description;
    int questionIndexes[hwQuestionCount];
};

void initializeHomeworkAssignments(HomeworkAssignment assignments[]);
void showHomeworkMenu(HomeworkRecord userRecords[],
    HomeworkAssignment assignments[],
    Question questionBank[]);

#endif
