#ifndef QUESTION_H
#define QUESTION_H

#include <string>

struct Question
{
    std::string text;
    std::string optionA;
    std::string optionB;
    std::string optionC;
    char correctAnswer;
    int category;
};

void initializeQuestionBank(Question questionBank[], int size);
void showHtmlLesson();
void showCssLesson();
void showJsLesson();

#endif

