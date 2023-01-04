/*
 * Copyright 2020-2022. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었다.
 */
%{
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

int yylex();
extern FILE* yyin;
extern int yylineno;
extern char *yytext;
static int num_errors = 0;
static class_list_t *program;
void yyerror(char const *s);
%}

%union {
    class_list_t *class_list;
    class_t *class;
    feature_list_t *feature_list;
    feature_t *feature;
    formal_list_t *formal_list;
    formal_t *formal;
    expr_list_t *expr_list;
    expr_t *expr;
    let_list_t *let_list;
    let_t *let;
    case_id_list_t *case_id_list;
    case_id_t *case_id;
    char *s;
    int i;
    bool b;
}

%token CLASS INHERITS IF THEN ELSE FI LET IN
%token WHILE LOOP POOL CASE OF DARROW ESAC
%token NEW ISVOID ASSIGN NOT LTE
%token <s> STRING TYPE ID
%token <i> INTEGER
%token <b> BOOLEAN

%type <class_list> class_list
%type <class> class
%type <feature_list> features
%type <feature> feature
%type <formal_list> formals
%type <formal> formal
%type <expr_list> exprs exprs_in_curlybrackets
%type <expr> expr
%type <let_list> let_ids
%type <let> let_id
%type <case_id_list> cases
%type <case_id> case

%left '<'
%left '='
%left '+' '-'
%left '*' '/'

%start program

%%
    
    program
    : class_list { program = $1; }
    ;
    
    class_list
    : class ';' class_list  { $$ = new_class_list($1, $3); }
    | class ';'             { $$ = new_class_list($1, NULL); }
    ;
    
    class
    : CLASS TYPE INHERITS TYPE '{' features '}' { $$ = new_class($2, $4, $6); }
    | CLASS TYPE INHERITS TYPE '{' '}'          { $$ = new_class($2, $4, NULL); }
    | CLASS TYPE '{' features '}'               { $$ = new_class($2, NULL, $4); }
    | CLASS TYPE '{' '}'                        { $$ = new_class($2, NULL, NULL); }
    ;
    
    features
    : feature ';' features  { $$ = new_feature_list($1, $3); }
    | feature ';'           { $$ = new_feature_list($1, NULL); }
    ;
    
    feature
    : ID '(' formals ')' ':' TYPE '{' exprs '}' { $$ = new_feature($1, $6, $3, $8, "f"); }
    | ID '(' ')' ':' TYPE '{' exprs '}'         { $$ = new_feature($1, $5, NULL, $7, "f"); }
    | ID ':' TYPE ASSIGN exprs                  { $$ = new_feature($1, $3, NULL, $5, "a"); }
    | ID ':' TYPE                               { $$ = new_feature($1, $3, NULL, NULL, "null"); }
    ;
    
    formals
    : formal ',' formals    { $$ = new_formal_list($1, $3); }
    | formal                { $$ = new_formal_list($1, NULL); }
    ;
    
    formal
    : ID ':' TYPE { $$ = new_formal($1, $3); }
    ;
    
    expr
    : ID ASSIGN expr                            { $$ = new_expr_assign(ASSIGN, $1, $3); }
    | expr '@' TYPE '.' ID '(' exprs ')'        { $$ = new_expr_at('@', $3, $5, $1, $7); }
    | expr '@' TYPE '.' ID '(' ')'              { $$ = new_expr_at('@', $3, $5, $1, NULL); }
    | expr '.' ID '(' exprs ')'                 { $$ = new_expr_dot('.', $3, $1, $5); }
    | expr '.' ID '(' ')'                       { $$ = new_expr_dot('.', $3, $1, NULL); }
    | ID '(' exprs ')'                          { $$ = new_expr_f('(', $1, $3); }
    | ID '(' ')'                                { $$ = new_expr_f('(', $1, NULL); }
    | IF exprs THEN exprs ELSE exprs FI         { $$ = new_expr_if(IF, $2, $4, $6); }
    | WHILE exprs LOOP exprs POOL               { $$ = new_expr_while(WHILE, $2, $4); }
    | '{' exprs_in_curlybrackets '}'            { $$ = new_expr_curlybrakets('{', $2); }
    | LET let_ids IN exprs                      { $$ = new_expr_let(LET, $2, $4); }
    | CASE expr OF cases ESAC                   { $$ = new_expr_case(CASE, $2, $4); }
    | NEW TYPE      { $$ = new_new($2);}
    | ISVOID expr   { $$ = new_expr(ISVOID, $2, NULL); }
    | expr '+' expr { $$ = new_expr('+', $1, $3); }
    | expr '-' expr { $$ = new_expr('-', $1, $3); }
    | expr '*' expr { $$ = new_expr('*', $1, $3); }
    | expr '/' expr { $$ = new_expr('/', $1, $3); }
    | '~' expr      { $$ = new_expr('~', $2, NULL); }
    | expr '<' expr { $$ = new_expr('<', $1, $3); }
    | expr LTE expr { $$ = new_expr(LTE, $1, $3); }
    | expr '=' expr { $$ = new_expr('=', $1, $3); }
    | NOT expr      { $$ = new_expr(NOT, $2, NULL); }
    | '(' expr ')'  { $$ = $2; }
    | ID            { $$ = new_str($1); }
    | INTEGER       { $$ = new_number($1); }
    | STRING        { $$ = new_str($1); }
    | BOOLEAN       { $$ = new_bool($1); }
    | error
    ;
    
    exprs
    : expr ',' exprs    { $$ = new_expr_list($1, $3); }
    | expr              { $$ = new_expr_list($1, NULL); }
    ;
    
    exprs_in_curlybrackets
    : expr ';' exprs_in_curlybrackets   { $$ = new_expr_list($1, $3); }
    | expr ';'                          { $$ = new_expr_list($1, NULL); }
    ;
    
    let_ids
    : let_id ',' let_ids        { $$ = new_let_list($1, $3); }
    | let_id                    { $$ = new_let_list($1, NULL); }
    ;
    
    let_id
    : ID ':' TYPE ASSIGN expr   { $$ = new_let($1, $3, $5); }
    | ID ':' TYPE               { $$ = new_let($1, $3, NULL); }
    ;
    
    cases
    : case ';' cases            { $$ = new_case_list($1, $3); }
    | case ';'                  { $$ = new_case_list($1, NULL); }
    ;
    
    case
    : ID ':' TYPE DARROW expr   { $$ = new_case($1, $3, $5); }
    ;
    
%%
void yyerror(char const *s)
{
    /*
     * 오류의 개수를 누적한다.
     */
    ++num_errors;
    /*
     * 문법 오류가 발생한 줄번호와 관련된 토큰을 출력한다.
     */
    if (yychar > 0)
        printf("%s in line %d at \"%s\"\n", s, yylineno, yytext);
    else
        printf("%s in line %d (unexpected EOF)\n", s, yylineno);
}

int main(int argc, char *argv[])
{
    /*
     * 스캔할 COOL 파일을 연다. 파일명이 없으면 표준입력이 사용된다.
     */
    if (argc > 1)
        if (!(yyin = fopen(argv[1],"r"))) {
            printf("\"%s\"는 잘못된 파일 경로입니다.\n", argv[1]);
            exit(1);
        }
    /*
     * 구문분석을 위해 수행한다.
     */
    yyparse();
    /*
     * 오류의 개수를 출력한다.
     */
    if (num_errors > 0)
         printf("%d error(s) found\n", num_errors);
    else
         show_class_list(program);

    return 0;
}
