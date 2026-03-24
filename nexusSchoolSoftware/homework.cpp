#include <iostream>
#include <string>
#include "homework.h"
#include "colors.h"
#include "gui.h"

using namespace std;

// Sets up the three pre-defined homework assignments, each covering one topic
void initializeHomeworkAssignments(HomeworkAssignment assignments[])
{
    // Homework 1 — HTML: uses question-bank indexes 0–9
    assignments[0].title = "HTML Fundamentals";
    assignments[0].description = "Practice HTML tags and page structure.";
    for (int i = 0; i < hwQuestionCount; i++)
        assignments[0].questionIndexes[i] = i;

    // Homework 2 — CSS: uses question-bank indexes 10–19
    assignments[1].title = "CSS Styling";
    assignments[1].description = "Practice CSS properties and selectors.";
    for (int i = 0; i < hwQuestionCount; i++)
        assignments[1].questionIndexes[i] = i + 10;

    // Homework 3 — JavaScript: uses question-bank indexes 20–29
    assignments[2].title = "JavaScript Basics";
    assignments[2].description = "Practice JavaScript fundamentals.";
    for (int i = 0; i < hwQuestionCount; i++)
        assignments[2].questionIndexes[i] = i + 20;
}

// Runs the interactive test for one homework assignment and stores the result
static void runHomeworkTest(HomeworkRecord& record,
    const HomeworkAssignment& assignment,
    Question questionBank[])
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle(assignment.title);

    int correct = 0;
    for (int i = 0; i < hwQuestionCount; i++)
    {
        clearScreen();
        printAsciiTitle();
        printCenteredTitle(assignment.title);
        
        Question& q = questionBank[assignment.questionIndexes[i]];

        printSectionTitle("Question " + to_string(i + 1) + " of " + to_string(hwQuestionCount));
        cout << "\n";
        printCenteredText(q.text);
        cout << "\n";

        string opts[3];
        opts[0] = "A)  " + q.optionA;
        opts[1] = "B)  " + q.optionB;
        opts[2] = "C)  " + q.optionC;
        int idx = arrowMenu(opts, 3);
        char answer = (char)('A' + idx);

        if (answer == q.correctAnswer)
        {
            cout << "\n" << getMintColor();
            printCenteredText("Correct!");
            cout << getResetColor();
            correct++;
        }
        else
        {
            cout << "\n" << getRoseColor();
            printCenteredText("Wrong!  Correct answer: " + string(1, q.correctAnswer));
            cout << getResetColor();
        }
        cout << "\n";
    }

    // Save result and mark as done
    record.score = correct;
    record.status = DONE;

    clearScreen();
    printAsciiTitle();
    printCenteredTitle(assignment.title);
    
    double pct = (double)correct / hwQuestionCount * 100.0;
    printSectionTitle("HOMEWORK RESULT");
    printLabelValue("Score  ", to_string(correct) + " / " + to_string(hwQuestionCount));
    printLabelValue("Result ", to_string((int)pct) + "%");
    cout << "\n";
    waitForEnter();
}

// Returns a short status label string for display in the menu
static string statusLabel(const HomeworkRecord& rec, const HomeworkAssignment& asgn)
{
    if (rec.status == UNDONE) return "[UNDONE]  " + asgn.title;
    if (rec.status == VIEWED) return "[VIEWED]  " + asgn.title;
    // DONE — show score inline
    return "[DONE " + to_string(rec.score) + "/" + to_string(hwQuestionCount) + "]  " + asgn.title;
}

// Homework hub: lets the user browse assignments, see their status, and launch tests
void showHomeworkMenu(HomeworkRecord userRecords[],
    HomeworkAssignment assignments[],
    Question questionBank[])
{
    int hwChoice = -1;
    while (hwChoice != homeworkCount)   // last option is "Back"
    {
        clearScreen();
        printAsciiTitle();
        printCenteredTitle("HOMEWORK");
        cout << "\n";

        // Build menu options — each shows the current status of the assignment
        string options[homeworkCount + 1];
        for (int i = 0; i < homeworkCount; i++)
            options[i] = statusLabel(userRecords[i], assignments[i]);
        options[homeworkCount] = "Back to Main Menu";

        hwChoice = arrowMenu(options, homeworkCount + 1);
        cout << "\n";

        if (hwChoice >= homeworkCount) break;   // "Back" selected

        // ── Detail / launch screen for the selected assignment ────────────────
        clearScreen();
        printAsciiTitle();
        printCenteredTitle(assignments[hwChoice].title);
        cout << "\n";
        printCenteredText(assignments[hwChoice].description);
        cout << "\n";

        // Build and show the current status string
        HomeworkRecord& rec = userRecords[hwChoice];
        string statusStr;
        if (rec.status == UNDONE) statusStr = "Not started";
        else if (rec.status == VIEWED) statusStr = "Viewed — not yet submitted";
        else    statusStr = "Done — " + to_string(rec.score) + " / " + to_string(hwQuestionCount)
            + "  (" + to_string((int)((double)rec.score / hwQuestionCount * 100)) + "%)";

        printLabelValue("Status", statusStr);
        cout << "\n";

        // Viewing the detail screen counts as "viewed" if still undone
        if (rec.status == UNDONE)
            rec.status = VIEWED;

        // Offer to start (or redo) the homework test
        string detailOptions[2];
        detailOptions[0] = (rec.status == DONE) ? "Redo Homework" : "Start Homework";
        detailOptions[1] = "Back";

        int detailChoice = arrowMenu(detailOptions, 2);
        if (detailChoice == 0)
            runHomeworkTest(rec, assignments[hwChoice], questionBank);
    }
}