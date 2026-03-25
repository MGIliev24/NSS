#include "question.h"

void initializeQuestionBank(Question qb[], int sz) {
    if (sz < 30) return;
    qb[0] ={"What does HTML stand for?","HyperText Markup Language","HighText Machine Language","Home Tool Markup Language",'A',0};
    qb[1] ={"Which tag defines a paragraph?","<para>","<p>","<paragraph>",'B',0};
    qb[2] ={"Which tag creates a hyperlink?","<link>","<a>","<href>",'B',0};
    qb[3] ={"Which tag is the largest heading?","<h6>","<head>","<h1>",'C',0};
    qb[4] ={"Which attribute sets the image source?","href","src","link",'B',0};
    qb[5] ={"Which tag defines an unordered list?","<ol>","<ul>","<list>",'B',0};
    qb[6] ={"Which element holds visible page content?","<body>","<head>","<title>",'A',0};
    qb[7] ={"Which tag defines a table row?","<tr>","<td>","<th>",'A',0};
    qb[8] ={"Which element sets the browser-tab title?","<meta>","<title>","<h1>",'B',0};
    qb[9] ={"Which tag inserts a line break?","<lb>","<br>","<break>",'B',0};
    qb[10]={"What does CSS stand for?","Cascading Style Sheets","Creative Style System","Computer Styled Sheets",'A',1};
    qb[11]={"Which property changes text color?","font-color","color","text-color",'B',1};
    qb[12]={"Which property changes the background color?","background","bgcolor","background-color",'C',1};
    qb[13]={"Which property controls text size?","font-size","text-size","size",'A',1};
    qb[14]={"How do you select all p elements in CSS?","p {}","#p {}",".p {}",'A',1};
    qb[15]={"How do you select id=main?",".main {}","#main {}","main {}",'B',1};
    qb[16]={"Which property sets outer space of element?","padding","margin","border",'B',1};
    qb[17]={"Which property sets inner space of element?","padding","margin","spacing",'A',1};
    qb[18]={"Which property sets the font type?","font-family","font-type","font-style",'A',1};
    qb[19]={"How do you write a CSS comment?","// comment","<!-- comment -->","/* comment */",'C',1};
    qb[20]={"Which HTML element holds JavaScript?","<js>","<script>","<javascript>",'B',2};
    qb[21]={"How do you show an alert saying Hello?","alert('Hello');","msg('Hello');","alertBox('Hello');",'A',2};
    qb[22]={"Which keyword declares a block-scoped var?","var","let","constant",'B',2};
    qb[23]={"How do you call function testFunction?","call testFunction();","testFunction();","run testFunction();",'B',2};
    qb[24]={"How do you write an if statement in JS?","if i = 5 then","if (i == 5)","if i == 5",'B',2};
    qb[25]={"How does a while loop start?","while i < 10","while (i < 10)","while (i < 10; i++)",'B',2};
    qb[26]={"Which method logs to the browser console?","console.write()","log.console()","console.log()",'C',2};
    qb[27]={"How do you write a single-line comment?","// comment","<!-- comment -->","/* comment */",'A',2};
    qb[28]={"Which operator adds numbers?","&","+","++",'B',2};
    qb[29]={"Which event fires on a mouse click?","onchange","onclick","onload",'B',2};
}

vector<LessonItem> getHtmlItems() {
    return {
        {"<html>","root element of the page"},{"<head>","metadata and page info"},
        {"<body>","visible content"},{"<h1>","main heading (h1-h6)"},
        {"<p>","paragraph"},{"<a>","hyperlink"},{"<img>","image"},
        {"<ul>/<ol>","unordered / ordered list"},{"<tr>","table row"},{"<br>","line break"}
    };
}
vector<LessonItem> getCssItems() {
    return {
        {"color","text color"},{"background-color","background color"},
        {"font-size","size of the text"},{"font-family","typeface / font stack"},
        {"margin","space outside the element"},{"padding","space inside border"},
        {"p {}","select all p elements"},{"#main {}","select element with id=main"},
        {".card {}","select elements with class=card"},{"/* comment */","CSS comment syntax"}
    };
}
vector<LessonItem> getJsItems() {
    return {
        {"let x = 0;","block-scoped variable"},{"function greet() {}","function definition"},
        {"if (score >= 10) {}","conditional statement"},{"for (let i=0;i<5;i++){}","for loop"},
        {"while (i < 10) {}","while loop"},{"alert('Hello');","browser alert box"},
        {"console.log(x);","write to browser console"},{"// comment","single-line comment"},
        {"onclick / onload","common HTML events"}
    };
}
