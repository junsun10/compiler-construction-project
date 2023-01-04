/*
 * Copyright 2020-2022. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었다.
 */
#ifndef _NODE_H_
#define _NODE_H_

// 아래 타입과 함수는 극히 일부에 불과하다.
// 학생들은 필요한 타입과 함수 시그니처를 추가한다.


typedef struct _class_list class_list_t;
typedef struct _class class_t;
typedef struct _feature_list feature_list_t;
typedef struct _feature feature_t;
typedef struct _formal_list formal_list_t;
typedef struct _formal formal_t;
typedef struct _expr_list expr_list_t;
typedef struct _expr expr_t;
typedef struct _let_list let_list_t;
typedef struct _let let_t;
typedef struct _case_id_list case_id_list_t;
typedef struct _case_id case_id_t;

struct _class_list {
    class_t *class;
    struct _class_list *next;
};

struct _class {
    char *type;
    char *inherited;
    // feature 목록이 들어갈 수 있도록 추가한다
    feature_list_t *features;
};

struct _feature_list {
    feature_t *feature;
    struct _feature_list *next;
};

struct _feature {
    char *id;
    char *type;
    formal_list_t *formals;
    expr_list_t *exprs;
    char *option;
};

struct _formal_list {
    formal_t *formal;
    struct _formal_list *next;
};

struct _formal {
    char *id;
    char *type;
};

struct _expr_list {
    expr_t *expr;
    struct _expr_list *next;
};

struct _expr {
    int type;
    union {
        int number;
        char *str;
        char *new;
        bool boolean;
        struct {
            char *id;
            struct _expr *expr;
        } assign;
        struct {
            struct _expr *left;
            struct _expr *right;
        } child;
        struct {
            char *type;
            char *id;
            struct _expr *first;
            struct _expr_list *exprs;
        } at;
        struct {
            char *id;
            struct _expr *first;
            struct _expr_list *exprs;
        } dot;
        struct {
            char *id;
            struct _expr_list *exprs;
        } f;
        struct {
            struct _expr_list *exprs1;
            struct _expr_list *exprs2;
            struct _expr_list *exprs3;
        } iffi;
        struct {
            struct _expr_list *exprs1;
            struct _expr_list *exprs2;
        } whileloop;
        struct {
            struct _expr_list *exprs;
        } curlybrakets;
        struct {
            struct _let_list *lets;
            struct _expr_list *exprs;
        } let;
        struct {
            struct _expr *expr;
            struct _case_id_list *cases;
        } caseesac;
    };
};

struct _let_list {
    let_t *let;
    struct _let_list *next;
};

struct _let {
    char *id;
    char *type;
    struct _expr *expr;
};

struct _case_id_list {
    case_id_t *case_id;
    struct _case_id_list *next;
};

struct _case_id {
    char *id;
    char *type;
    struct _expr *expr;
};

void show_expr(expr_t *expr);
void show_expr_list(expr_list_t *expr_list);
void show_case(case_id_t *case_id);
void show_case_list(case_id_list_t *case_id_list);
void show_formal_list(formal_list_t *formal_list);
void show_feature_list(feature_list_t *feature_list);
void show_class_list(class_list_t *class_list);

class_t *new_class(char *type, char *inherited, feature_list_t *features);
class_list_t *new_class_list(class_t *class, class_list_t *next);

feature_t *new_feature(char *id, char *type, formal_list_t *formals, expr_list_t *exprs, char *option);
feature_list_t *new_feature_list(feature_t *feature, feature_list_t *next);

formal_t *new_formal(char *id, char *type);
formal_list_t *new_formal_list(formal_t *formal, formal_list_t *next);


expr_t *new_expr_assign(int type, char *id, expr_t *expr);
expr_t *new_number(int number);
expr_t *new_str(char *str);
expr_t *new_new(char *new);
expr_t *new_bool(bool boolean);
expr_t *new_expr(int type, expr_t *left, expr_t *right);
expr_t *new_expr_at(int type, char *t, char *id, expr_t *first, expr_list_t *exprs);
expr_t *new_expr_dot(int type, char *id, expr_t *first, expr_list_t *exprs);
expr_t *new_expr_if(int type, expr_list_t *exprs1, expr_list_t *exprs2, expr_list_t *exprs3);
expr_t *new_expr_while(int type, expr_list_t *exprs1, expr_list_t *exprs2);
expr_t *new_expr_f(int type, char *id, expr_list_t *exprs);
expr_t *new_expr_curlybrakets(int type, expr_list_t *exprs);
expr_t *new_expr_let(int type, let_list_t *lets, expr_list_t *exprs);
expr_t *new_expr_case(int type, expr_t *expr1, case_id_list_t *cases);

expr_list_t *new_expr_list(expr_t *expr, expr_list_t *next);

let_t *new_let(char *id, char *type, expr_t *expr);
let_list_t *new_let_list(let_t *let, let_list_t *next);
case_id_t *new_case(char *id, char*type, expr_t *expr);
case_id_list_t *new_case_list(case_id_t *case_id, case_id_list_t *next);

#endif
