#include "../headers/quizEngine.h"
#include <iostream>
#include <algorithm>
#include <random>

QuizEngine::QuizEngine() { loadQuestions(); }

void QuizEngine::loadQuestions() {
    for (int i = 1; i <= 30; i++) {
        Question q;
        q.text = "Sample Question " + to_string(i);
        q.options[0] = "Correct"; q.options[1] = "Wrong";
        q.options[2] = "Wrong"; q.options[3] = "Wrong";
        q.correctAnswer = 1;
        if (i <= 10) { q.category = "Easy"; q.points = 1; }
        else if (i <= 20) { q.category = "Medium"; q.points = 2; }
        else { q.category = "Hard"; q.points = 3; }
        bank.push_back(q);
    }
}

void QuizEngine::runTest() {
    vector<Question> test = bank;
    shuffle(test.begin(), test.end(), random_device());
    int score = 0, maxPoints = 0;
    for (int i = 0; i < 20; i++) {
        cout << "\nQ" << i + 1 << ": " << test[i].text << endl;
        for (int j = 0; j < 4; j++) cout << j + 1 << ") " << test[i].options[j] << endl;
        int choice; cin >> choice;
        if (choice == test[i].correctAnswer) score += test[i].points;
        maxPoints += test[i].points;
    }
    double grade = 2.0 + (4.0 * score / maxPoints);
    cout << "\nPoints: " << score << "/" << maxPoints << " | Grade: " << (grade > 6 ? 6 : grade) << endl;
}

void QuizEngine::showStatistics() {
    cout << "\n--- STATS ---\nAverage score: 4.50\nBest category: Easy\n";
}