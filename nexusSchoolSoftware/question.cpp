#include <iostream>
#include <string>
#include "question.h"
#include "colors.h"
#include "gui.h"

using namespace std;

// Centers and prints a "tag  -  desc" item within the box, with a fixed left indent
static void printItem(const string& tag, const string& desc)
{
    static const int INDENT = 6;
    string line = string(INDENT, ' ') + tag + "  -  " + desc;
    int p = (92 - (int)line.length()) / 2;
    if (p < 0) p = 0;
    cout << string(14, ' ') << string(p, ' ') << line << "\n";
}

// ─── Lesson screens ───────────────────────────────────────────────────────────
// Each function clears the screen, displays the lesson content, and blocks
// until the user presses Enter to return to the lessons menu.

void showHtmlLesson()
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("HTML BASICS");
    printCenteredText("HyperText Markup Language - structures web pages.");
    printSectionTitle("Core Elements");
    printItem("<html>", "root element of the page");
    printItem("<head>", "metadata and page information");
    printItem("<body>", "visible content");
    printItem("<h1>", "main heading  (h1 to h6)");
    printItem("<p>", "paragraph");
    printItem("<a>", "hyperlink");
    printItem("<img>", "image");
    printItem("<ul>/<ol>", "unordered / ordered list");
    printItem("<tr>", "table row");
    printItem("<br>", "line break");
    printSectionTitle("Exercise Idea");
    printCenteredText("Build a page: heading, paragraph, link to your school.");
    cout << "\n";
    waitForEnter();
}

void showCssLesson()
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("CSS BASICS");
    printCenteredText("Cascading Style Sheets - controls the visual style of HTML.");
    printSectionTitle("Common Properties");
    printItem("color", "text color");
    printItem("background-color", "background color");
    printItem("font-size", "size of the text");
    printItem("font-family", "typeface / font stack");
    printItem("margin", "space outside the element");
    printItem("padding", "space inside the element border");
    printItem("p {}", "select all p elements");
    printItem("#main {}", "select element with id=main");
    printItem(".card {}", "select elements with class=card");
    printItem("/* comment */", "CSS comment syntax");
    printSectionTitle("Exercise Idea");
    printCenteredText("Style your HTML page: colors, font size, spacing.");
    cout << "\n";
    waitForEnter();
}

void showJsLesson()
{
    clearScreen();
    printAsciiTitle();
    printCenteredTitle("JAVASCRIPT BASICS");
    printCenteredText("JavaScript adds logic and interactivity to web pages.");
    printSectionTitle("Core Concepts");
    printItem("let x = 0;", "block-scoped variable");
    printItem("function greet() {}", "function definition");
    printItem("if (score >= 10) {}", "conditional statement");
    printItem("for (let i=0;i<5;i++){}", "for loop");
    printItem("while (i < 10) {}", "while loop");
    printItem("alert('Hello');", "browser alert box");
    printItem("console.log(x);", "write to browser console");
    printItem("// comment", "single-line comment");
    printItem("onclick / onload", "common HTML events");
    printSectionTitle("Exercise Idea");
    printCenteredText("Show a message when a button is clicked.");
    cout << "\n";
    waitForEnter();
}

// Populates the question bank with 30 questions — 10 per topic (HTML, CSS, JS).
// Questions are stored in order: indices 0-9 = HTML, 10-19 = CSS, 20-29 = JS.
// The last field on each row is the topic index used by the test and statistics modules.
void initializeQuestionBank(Question questionBank[], int size)
{
    if (size < 30) return;  // Guard against an undersized array being passed in

    // HTML questions (topic 0)
    questionBank[0] = { "What does HTML stand for?",                    "HyperText Markup Language", "HighText Machine Language",   "Home Tool Markup Language",    'A', 0 };
    questionBank[1] = { "Which tag defines a paragraph?",               "<para>",                    "<p>",                         "<paragraph>",                  'B', 0 };
    questionBank[2] = { "Which tag creates a hyperlink?",               "<link>",                    "<a>",                         "<href>",                       'B', 0 };
    questionBank[3] = { "Which tag is the largest heading?",            "<h6>",                      "<head>",                      "<h1>",                         'C', 0 };
    questionBank[4] = { "Which attribute sets the image source?",       "href",                      "src",                         "link",                         'B', 0 };
    questionBank[5] = { "Which tag defines an unordered list?",         "<ol>",                      "<ul>",                        "<list>",                       'B', 0 };
    questionBank[6] = { "Which element holds visible page content?",    "<body>",                    "<head>",                      "<title>",                      'A', 0 };
    questionBank[7] = { "Which tag defines a table row?",               "<tr>",                      "<td>",                        "<th>",                         'A', 0 };
    questionBank[8] = { "Which element sets the browser-tab title?",    "<meta>",                    "<title>",                     "<h1>",                         'B', 0 };
    questionBank[9] = { "Which tag inserts a line break?",              "<lb>",                      "<br>",                        "<break>",                      'B', 0 };

    // CSS questions (topic 1)
    questionBank[10] = { "What does CSS stand for?",                     "Cascading Style Sheets",    "Creative Style System",       "Computer Styled Sheets",       'A', 1 };
    questionBank[11] = { "Which property changes text color?",           "font-color",                "color",                       "text-color",                   'B', 1 };
    questionBank[12] = { "Which property changes the background color?", "background",                "bgcolor",                     "background-color",             'C', 1 };
    questionBank[13] = { "Which property controls text size?",           "font-size",                 "text-size",                   "size",                         'A', 1 };
    questionBank[14] = { "How do you select all p elements in CSS?",     "p {}",                      "#p {}",                       ".p {}",                        'A', 1 };
    questionBank[15] = { "How do you select id=main?",                   ".main {}",                  "#main {}",                    "main {}",                      'B', 1 };
    questionBank[16] = { "Which property sets outer space of element?",  "padding",                   "margin",                      "border",                       'B', 1 };
    questionBank[17] = { "Which property sets inner space of element?",  "padding",                   "margin",                      "spacing",                      'A', 1 };
    questionBank[18] = { "Which property sets the font type?",           "font-family",               "font-type",                   "font-style",                   'A', 1 };
    questionBank[19] = { "How do you write a CSS comment?",              "// comment",                "<!-- comment -->",             "/* comment */",                'C', 1 };

    // JavaScript questions (topic 2)
    questionBank[20] = { "Which HTML element holds JavaScript?",         "<js>",                      "<script>",                    "<javascript>",                 'B', 2 };
    questionBank[21] = { "How do you show an alert saying Hello?",       "alert('Hello');",           "msg('Hello');",               "alertBox('Hello');",           'A', 2 };
    questionBank[22] = { "Which keyword declares a block-scoped var?",   "var",                       "let",                         "constant",                     'B', 2 };
    questionBank[23] = { "How do you call function testFunction?",       "call testFunction();",      "testFunction();",             "run testFunction();",          'B', 2 };
    questionBank[24] = { "How do you write an if statement in JS?",      "if i = 5 then",             "if (i == 5)",                 "if i == 5",                    'B', 2 };
    questionBank[25] = { "How does a while loop start?",                 "while i < 10",              "while (i < 10)",              "while (i < 10; i++)",          'B', 2 };
    questionBank[26] = { "Which method logs to the browser console?",    "console.write()",           "log.console()",               "console.log()",                'C', 2 };
    questionBank[27] = { "How do you write a single-line comment?",      "// comment",                "<!-- comment -->",             "/* comment */",                'A', 2 };
    questionBank[28] = { "Which operator adds numbers?",                 "&",                         "+",                           "++",                           'B', 2 };
    questionBank[29] = { "Which event fires on a mouse click?",          "onchange",                  "onclick",                     "onload",                       'B', 2 };
}