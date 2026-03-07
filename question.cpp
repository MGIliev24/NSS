#include <iostream>
#include <string>
#include "question.h"
#include "colors.h"
#include "gui.h"

using namespace std;

void showHtmlLesson()
{
    clearScreen();
    printCenteredTitle("HTML BASICS");
    cout << "HTML (HyperText Markup Language) is used to structure web pages.\n\n";
    printSectionTitle("Main elements");
    cout << "<html>  - root element of the page\n";
    cout << "<head>  - metadata and page information\n";
    cout << "<body>  - visible content\n";
    cout << "<h1>    - main heading\n";
    cout << "<p>     - paragraph\n";
    cout << "<a>     - hyperlink\n";
    cout << "<img>   - image\n\n";
    printSectionTitle("Exercise idea");
    cout << "Create a small page with a heading, a paragraph and a link to your school.\n";
    waitForEnter();
}

void showCssLesson()
{
    clearScreen();
    printCenteredTitle("CSS BASICS");
    cout << "CSS (Cascading Style Sheets) controls the visual style of HTML.\n\n";
    printSectionTitle("Common properties");
    cout << "color            - text color\n";
    cout << "background-color - background color\n";
    cout << "font-size        - size of the text\n";
    cout << "margin           - space outside the element\n";
    cout << "padding          - space inside the element border\n\n";
    printSectionTitle("Exercise idea");
    cout << "Style your HTML page: change colors, font size and add some spacing.\n";
    waitForEnter();
}

void showJsLesson()
{
    clearScreen();
    printCenteredTitle("JAVASCRIPT BASICS");
    cout << "JavaScript adds logic and interactivity to web pages.\n\n";
    printSectionTitle("Core concepts");
    cout << "Variables  - let score = 0;\n";
    cout << "Functions  - function greet() { }\n";
    cout << "Conditions - if (score >= 10) { }\n";
    cout << "Loops      - for (let i = 0; i < 5; i++) { }\n";
    cout << "Events     - onclick, onmouseover, keydown\n\n";
    printSectionTitle("Exercise idea");
    cout << "Write a small script that shows a message when a button is clicked.\n";
    waitForEnter();
}

void initializeQuestionBank(Question questionBank[], int size)
{
    if (size < 30)
    {
        return;
    }

    // 10 HTML questions (0..9), category = 0
    questionBank[0] = {"What does HTML stand for?",
                       "HyperText Markup Language",
                       "HighText Machine Language",
                       "Home Tool Markup Language",
                       'A', 0};

    questionBank[1] = {"Which tag defines a paragraph in HTML?",
                       "<para>",
                       "<p>",
                       "<paragraph>",
                       'B', 0};

    questionBank[2] = {"Which tag is used to create a hyperlink?",
                       "<link>",
                       "<a>",
                       "<href>",
                       'B', 0};

    questionBank[3] = {"Which tag is used for the largest heading?",
                       "<h6>",
                       "<head>",
                       "<h1>",
                       'C', 0};

    questionBank[4] = {"Which attribute sets the image source?",
                       "href",
                       "src",
                       "link",
                       'B', 0};

    questionBank[5] = {"Which tag defines an unordered list?",
                       "<ol>",
                       "<ul>",
                       "<list>",
                       'B', 0};

    questionBank[6] = {"Which element contains the visible page content?",
                       "<body>",
                       "<head>",
                       "<title>",
                       'A', 0};

    questionBank[7] = {"Which tag is used for a table row?",
                       "<tr>",
                       "<td>",
                       "<th>",
                       'A', 0};

    questionBank[8] = {"Which element defines the title shown in the browser tab?",
                       "<meta>",
                       "<title>",
                       "<h1>",
                       'B', 0};

    questionBank[9] = {"Which tag inserts a line break?",
                       "<lb>",
                       "<br>",
                       "<break>",
                       'B', 0};

    // 10 CSS questions (10..19), category = 1
    questionBank[10] = {"What does CSS stand for?",
                        "Cascading Style Sheets",
                        "Creative Style System",
                        "Computer Styled Sheets",
                        'A', 1};

    questionBank[11] = {"Which property changes the text color?",
                        "font-color",
                        "color",
                        "text-color",
                        'B', 1};

    questionBank[12] = {"Which property changes the background color?",
                        "background",
                        "bgcolor",
                        "background-color",
                        'C', 1};

    questionBank[13] = {"Which property controls the text size?",
                        "font-size",
                        "text-size",
                        "size",
                        'A', 1};

    questionBank[14] = {"How to select all <p> elements in CSS?",
                        "p {}",
                        "#p {}",
                        ".p {}",
                        'A', 1};

    questionBank[15] = {"How to select an element with id 'main'?",
                        ".main {}",
                        "#main {}",
                        "main {}",
                        'B', 1};

    questionBank[16] = {"Which property sets the outer space of an element?",
                        "padding",
                        "margin",
                        "border",
                        'B', 1};

    questionBank[17] = {"Which property sets the inner space of an element?",
                        "padding",
                        "margin",
                        "spacing",
                        'A', 1};

    questionBank[18] = {"Which property sets the font type?",
                        "font-family",
                        "font-type",
                        "font-style",
                        'A', 1};

    questionBank[19] = {"How do you write a CSS comment?",
                        "// comment",
                        "<!-- comment -->",
                        "/* comment */",
                        'C', 1};

    // 10 JavaScript questions (20..29), category = 2
    questionBank[20] = {"Inside which HTML element do we put JavaScript code?",
                        "<js>",
                        "<script>",
                        "<javascript>",
                        'B', 2};

    questionBank[21] = {"How do you write 'Hello' in an alert box?",
                        "alert('Hello');",
                        "msg('Hello');",
                        "alertBox('Hello');",
                        'A', 2};

    questionBank[22] = {"Which keyword declares a block-scoped variable?",
                        "var",
                        "let",
                        "constant",
                        'B', 2};

    questionBank[23] = {"How do you call a function named testFunction?",
                        "call testFunction();",
                        "testFunction();",
                        "run testFunction();",
                        'B', 2};

    questionBank[24] = {"How do you write an if statement in JavaScript?",
                        "if i = 5 then",
                        "if (i == 5)",
                        "if i == 5",
                        'B', 2};

    questionBank[25] = {"How does a while loop start?",
                        "while i < 10",
                        "while (i < 10)",
                        "while (i < 10; i++)",
                        'B', 2};

    questionBank[26] = {"Which method writes a message in the browser console?",
                        "console.write()",
                        "log.console()",
                        "console.log()",
                        'C', 2};

    questionBank[27] = {"How do you add a single-line comment in JS?",
                        "// comment",
                        "<!-- comment -->",
                        "/* comment */",
                        'A', 2};

    questionBank[28] = {"Which operator is used to add numbers?",
                        "&",
                        "+",
                        "++",
                        'B', 2};

    questionBank[29] = {"Which event fires when a user clicks on an element?",
                        "onchange",
                        "onclick",
                        "onload",
                        'B', 2};
}

