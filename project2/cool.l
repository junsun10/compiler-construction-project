/*
 * Copyright 2020-2022. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었다.
 */
%option noinput nounput yylineno
%{
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"
#include "cool.tab.h"
int lineNo = 1;
int comment = 0;
%}

NEWLINE     (\r\n|\n)
WHITESPACE  [ \t]+
DASHCOMMENT --.*\n
INTEGER   [0-9]*
ID [a-z]([a-zA-Z0-9]*_*)*
TYPE [A-Z]([a-zA-Z0-9]*_*)*
STRING \"(\\.|[^\n"\\])*\"

%%
                
{WHITESPACE}    /* skip */
{NEWLINE}       /* skip */
{DASHCOMMENT}   /* skip */

\(\*.*\*\)
\(\* { comment++; }
\*\) { comment--; }

(?i:class)           { if(comment==0){ return CLASS; } }
(?i:inherits)        { if(comment==0){ return INHERITS; } }

[Ii]f       { if(comment==0){ return IF; } }
then        { if(comment==0){ return THEN; } }
ELSE|else   { if(comment==0){ return ELSE; } }
fi          { if(comment==0){ return FI; } }
let         { if(comment==0){ return LET; } }
in          { if(comment==0){ return IN; } }
while       { if(comment==0){ return WHILE; } }
loop        { if(comment==0){ return LOOP; } }
pool        { if(comment==0){ return POOL; } }
case        { if(comment==0){ return CASE; } }
of          { if(comment==0){ return OF; } }
esac        { if(comment==0){ return ESAC; } }
new         { if(comment==0){ return NEW; } }
isvoid      { if(comment==0){ return ISVOID; } }
not         { if(comment==0){ return NOT; } }

true|false  { if(comment==0){ if (strcmp(yytext,"true") == 0){ yylval.b = true; } else { yylval.b = false; } return BOOLEAN; } }

{TYPE}      { if(comment==0){ yylval.s = strdup(yytext); return TYPE; } }
{ID}        { if(comment==0){ yylval.s = strdup(yytext); return ID; } }
{INTEGER}   { if(comment==0){ yylval.i = atoi(yytext); return INTEGER; } }
{STRING}    { if(comment==0){ yylval.s = strdup(yytext); return STRING; } }

 "("    { if(comment==0) { return '('; } }
 ")"    { if(comment==0) { return ')'; } }
 "{"    { if(comment==0) { return '{'; } }
 "}"    { if(comment==0) { return '}'; } }
 "<="   { if(comment==0) { return LTE; } }
 "<-"   { if(comment==0) { return ASSIGN; } }
 "<"    { if(comment==0) { return '<'; } }
 "=>"   { if(comment==0) { return DARROW; } }
 "="    { if(comment==0) { return '='; } }
 ","    { if(comment==0) { return ','; } }
 ";"    { if(comment==0) { return ';'; } }
 ":"    { if(comment==0) { return ':'; } }
 "."    { if(comment==0) { return '.'; } }
 "+"    { if(comment==0) { return '+'; } }
 "-"    { if(comment==0) { return '-'; } }
 "*"    { if(comment==0) { return '*'; } }
 "/"    { if(comment==0) { return '/'; } }
 "~"    { if(comment==0) { return '~'; } }
 "@"    { if(comment==0) { return '@'; } }

 "\'"
 "|"
 "\\"
 "!"
 "#"
 

 .      {
            if(comment==0) {}
            else {
                fprintf(stderr, "Skip unknown character %s in line %d\n", yytext, yylineno);
            }
        }

%%

