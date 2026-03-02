#ifndef QUESTION_H
#define QUESTION_H
#include <string>

using namespace std;

struct Question {
    string text;
    string category;
    string options[4];
    int correctAnswer;
    int points;
};

#endif