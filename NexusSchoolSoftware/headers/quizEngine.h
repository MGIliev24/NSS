#ifndef QUIZENGINE_H
#define QUIZENGINE_H
#include <vector>
#include "question.h"

using namespace std;

class QuizEngine {
private:
    vector<Question> bank;
    void loadQuestions();
public:
    QuizEngine();
    void runTest();
    void showStatistics();
};

#endif