#ifndef QUESTION_H
#define QUESTION_H
#include <string>
using namespace std;

struct Question
{
    string text;
    string optionA;
    string optionB;
    string optionC;
    char correctAnswer;
    int category;
};

const int questionBankSize = 30;

void initializeQuestionBank(Question questionBank[], int size);
void showHtmlLesson();
void showCssLesson();
void showJsLesson();

#endif