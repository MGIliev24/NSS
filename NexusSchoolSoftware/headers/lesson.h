#ifndef LESSON_H
#define LESSON_H
#include <string>
#include <vector>

using namespace std;

struct Lesson {
    string title;
    string content;
};

class SchoolModule {
public:
    vector<Lesson> lessons;
    SchoolModule();
    void displayLesson(int index);
};

#endif