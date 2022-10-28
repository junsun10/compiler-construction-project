/*
 * Copyright 2020-2022. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었다.
 */
%option noinput nounput
%{
#include <stdio.h>
#include <stdlib.h>
#include "cool.tab.h"
int lineNo = 1;
int comment = 0;
%}

NEWLINE     (\r\n|\n)
WHITESPACE  [ \t]+
INTEGER   [0-9]*
ID [a-z]([a-zA-Z0-9]*_*)*
STRING \"(\\.|[^\n"\\])*\"

%%

{WHITESPACE}    /* SKIP */
{NEWLINE}       { lineNo++; }

--.*
\(\*.*\*\) //{ printf("%03d: oneline comment\n",lineNo); }
\(\* { comment++; /*printf("%03d: +1 %d\n",lineNo, comment);*/ }
\*\) { comment--; /*printf("%03d: -1 %d\n",lineNo, comment);*/ }


[Cc]lass { if(comment==0){ return CLASS; } }
inherit[sS]    { if(comment==0){ return INHERITS; } }
[Ii]f       { if(comment==0){ return IF; } }
then        { if(comment==0){ return THEN; } }
ELSE|else   { if(comment==0){ return ELSE; } }
fi          { if(comment==0){ return FI; } }
while       { if(comment==0){ return WHILE; } }
loop        { if(comment==0){ return LOOP; } }
pool        { if(comment==0){ return POOL; } }
let         { if(comment==0){ return LET; } }
in          { if(comment==0){ return IN; } }
case        { if(comment==0){ return CASE; } }
of          { if(comment==0){ return OF; } }
esac        { if(comment==0){ return ESAC; } }
new         { if(comment==0){ return NEW; } }
isvoid      { if(comment==0){ return ISVOID; } }
not         { if(comment==0){ return NOT; } }
true        { if(comment==0){ return TRUE; } }
false       { if(comment==0){ return FALSE; } }
[A-Z]([a-zA-Z0-9]*_*)* { if(comment==0){ return TYPE; } }
{ID}        { if(comment==0){ return ID; } }
{INTEGER}   { if(comment==0){ return INTEGER; } }
{STRING}    { if(comment==0){ return STRING; } }
"("         { if(comment==0){ return LPAREN; } }
")"         { if(comment==0){ return RPAREN; } }
"{"         { if(comment==0){ return LBRACE; } }
"}"         { if(comment==0){ return RBRACE; } }
"<="        { if(comment==0){ return LTE; } }
"<-"        { if(comment==0){ return ASSIGN; } }
"<"         { if(comment==0){ return LT; } }
"=>"        { if(comment==0){ return DARROW; } }
"="         { if(comment==0){ return EQUAL; } }
","         { if(comment==0){ return COMMA; } }
";"         { if(comment==0){ return SEMICOLON; } }
":"         { if(comment==0){ return COLON; } }
"."         { if(comment==0){ return DOT; } }
"+"         { if(comment==0){ return PLUS; } }
"-"         { if(comment==0){ return MINUS; } }
"*"         { if(comment==0){ return MUL; } }
"/"         { if(comment==0){ return DIV; } }
"~"         { if(comment==0){ return NEG; } }
"@"         { if(comment==0){ return ATSIGN; } }

.       {
    if (comment > 0) {}
    else {
    fprintf(stderr, "Invalid character %s in line %d\n", yytext, lineNo);
          exit(1);
    }
    }

%%

int main(int argc, char *argv[])
{
    int token;

    /*
     * 스캔할 COOL 파일을 연다. 파일명이 없으면 표준입력이 사용된다.
     */
    if (argc > 1)
        if (!(yyin = fopen(argv[1],"r"))) {
            printf("\"%s\"는 잘못된 파일 경로입니다.\n", argv[1]);
            exit(1);
        }
    /* 
     * 토큰을 식별할 때마다 줄번호, 타입, 문자열(lexeme)을 출력한다
     */
    for (token = yylex(); token != YY_NULL; token = yylex())
        printf("%03d:[%s] %s\n", lineNo, tokenName[token-100], yytext);
}
