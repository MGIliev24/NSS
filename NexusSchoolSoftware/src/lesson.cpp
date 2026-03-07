#include "../headers/lesson.h"
#include <iostream>

SchoolModule::SchoolModule() {
    lessons.push_back({ "1. Variables", "In C++, variables are used to store data." });
    lessons.push_back({ "2. Conditions", "If-statements help make decisions." });
    lessons.push_back({ "3. Loops", "Loops repeat code multiple times." });
}

void SchoolModule::displayLesson(int index) {
    if (index >= 0 && index < (int)lessons.size()) {
        cout << "\n--- " << lessons[index].title << " ---\n";
        cout << lessons[index].content << "\n\nPress Enter to return...";
        cin.ignore(); cin.get();
    }
}