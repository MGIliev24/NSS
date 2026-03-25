#pragma once
#include <string>
#include <vector>
using namespace std;

struct Question {
    string text, optionA, optionB, optionC;
    char correctAnswer;
    int  category; // 0=HTML 1=CSS 2=JS
};
const int questionBankSize = 30;

struct LessonItem { string tag, desc; };

void initializeQuestionBank(Question qb[], int sz);
vector<LessonItem> getHtmlItems();
vector<LessonItem> getCssItems();
vector<LessonItem> getJsItems();
