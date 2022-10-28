/*
 * Copyright 2020-2022. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었다.
 */

/*
 * COOL언어 토큰의 값과 이름을 정의한다.
 * yylex()가 토큰을 인식하면 아래 정의된 값을 리턴한다.
 * 입력의 끝을 의미하는 YY_NULL은 0이므로 토큰 값은 0보다 커야 한다.
 */
#define CLASS       100
#define INHERITS    101
#define IF          102
#define THEN        103
#define ELSE        104
#define FI          105
#define WHILE       106
#define LOOP        107
#define POOL        108
#define LET         109
#define IN          110
#define CASE        111
#define OF          112
#define ESAC        113
#define NEW         114
#define ISVOID      115
#define NOT         116
#define TRUE        117
#define FALSE       118
#define TYPE        119
#define ID          120
#define INTEGER     121
#define STRING      122
#define LPAREN      123
#define RPAREN      124
#define LBRACE      125
#define RBRACE      126
#define LTE         127
#define ASSIGN      128
#define LT          129
#define DARROW      130
#define EQUAL       131
#define COMMA       132
#define SEMICOLON   133
#define COLON       134
#define DOT         135
#define PLUS        136
#define MINUS       137
#define MUL         138
#define DIV         139
#define NEG         140
#define ATSIGN      141

char *tokenName[] = {
    "CLASS",
    "INHERITS",
    "IF",
    "THEN",
    "ELSE",
    "FI",
    "WHILE",
    "LOOP",
    "POOL",
    "LET",
    "IN",
    "CASE",
    "OF",
    "ESAC",
    "NEW",
    "ISVOID",
    "NOT",
    "TRUE",
    "FALSE",
    "TYPE",
    "ID",
    "INTEGER",
    "STRING",
    "LPAREN",
    "RPAREN",
    "LBRACE",
    "RBRACE",
    "LTE",
    "ASSIGN",
    "LT",
    "DARROW",
    "EQUAL",
    "COMMA",
    "SEMICOLON",
    "COLON",
    "DOT",
    "PLUS",
    "MINUS",
    "MUL",
    "DIV",
    "NEG",
    "ATSIGN"
};
