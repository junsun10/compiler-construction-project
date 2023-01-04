/*
 * Copyright 2020-2022. Heekuck Oh, all rights reserved
 * 이 프로그램은 한양대학교 ERICA 소프트웨어학부 재학생을 위한 교육용으로 제작되었다.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "node.h"
#include "cool.tab.h"

// 아래 함수는 필요한 전체 함수 중 극히 일부에 불과하다.
// 학생들은 필요한 함수를 추가한다.

void show_let(let_t *let)
{
    printf("%s[%s]", let->id, let->type);
    if (let->expr != NULL) {
        printf("<-");
        show_expr(let->expr);
    }
}

void show_let_list(let_list_t *let_list)
{
    let_list_t *temp = let_list;
    while (temp != NULL) {
        show_let(temp->let);
        printf(" ");
        temp = temp->next;
    }
}

void show_case(case_id_t *case_id)
{
    printf("%s[%s]=>", case_id->id, case_id->type);
    show_expr(case_id->expr);
}

void show_case_list(case_id_list_t *case_id_list)
{
    case_id_list_t *temp = case_id_list;
    while (temp != NULL) {
        show_case(temp->case_id);
        printf(" ");
        temp = temp->next;
    }
}

void show_expr(expr_t *expr)
{
    switch (expr->type){
        
        case ASSIGN:
            printf("%s", expr->assign.id);
            printf("<-");
            show_expr(expr->assign.expr);
            break;
            
        case '@':
            show_expr(expr->at.first);
            printf(".");
            printf("[%s]", expr->at.type);
            printf("%s", expr->at.id);
            printf("(");
            if (expr->at.exprs != NULL) {
                show_expr_list(expr->at.exprs);
            }
            printf(")");
            break;
            
        case '.':
            show_expr(expr->at.first);
            printf(".");
            printf("%s", expr->at.id);
            printf("(");
            if (expr->at.exprs != NULL) {
                show_expr_list(expr->at.exprs);
            }
            printf(")");
            break;
            
        case '(':
            printf("%s", expr->at.id);
            printf("(");
            if (expr->at.exprs != NULL) {
                show_expr_list(expr->at.exprs);
            }
            printf(")");
            break;
            
        case IF:
            printf("(if");
            show_expr_list(expr->iffi.exprs1);
            show_expr_list(expr->iffi.exprs2);
            show_expr_list(expr->iffi.exprs3);
            printf(")");
            break;
            
        case WHILE:
            printf("(while");
            show_expr_list(expr->iffi.exprs1);
            show_expr_list(expr->iffi.exprs2);
            printf(")");
            break;
            
        case '{':
            printf("(");
            show_expr_list(expr->curlybrakets.exprs);
            printf(")");
            break;
            
        case LET:
            printf("(let (");
            show_let_list(expr->let.lets);
            printf(")");
            show_expr_list(expr->let.exprs);
            printf(")");
            break;
            
        case CASE:
            printf("(case ");
            show_expr(expr->caseesac.expr);
            printf(" (");
            show_case_list(expr->caseesac.cases);
            printf("))");
            break;
            
        case NEW:
            printf("(new ");
            printf("%s",expr->str);
            printf(")");
            break;
            
        case ISVOID:
            printf("(isvoid ");
            show_expr(expr->child.left);
            if (expr->child.right != NULL) {
                printf(" ");
                show_expr(expr->child.right);
            }
            printf(")");
            break;
            
        case '+':
            printf("(+ ");
            show_expr(expr->child.left);
            printf(" ");
            show_expr(expr->child.right);
            printf(")");
            break;
            
        case '-':
            printf("(- ");
            show_expr(expr->child.left);
            if (expr->child.right != NULL) {
                printf(" ");
                show_expr(expr->child.right);
            }
            printf(")");
            break;
        
        case '*':
            printf("(* ");
            show_expr(expr->child.left);
            printf(" ");
            show_expr(expr->child.right);
            printf(")");
            break;
            
        case '/':
            printf("(/ ");
            show_expr(expr->child.left);
            printf(" ");
            show_expr(expr->child.right);
            printf(")");
            break;
            
        case '~':
            printf("(~");
            show_expr(expr->child.left);
            if (expr->child.right != NULL) {
                printf(" ");
                show_expr(expr->child.right);
            }
            printf(")");
            break;
        
        case '<':
            printf("(<");
            show_expr(expr->child.left);
            printf(" ");
            show_expr(expr->child.right);
            printf(")");
            break;
        
        case LTE:
            printf("(<=");
            show_expr(expr->child.left);
            printf(" ");
            show_expr(expr->child.right);
            printf(")");
            break;
            
        case '=':
            printf("(=");
            show_expr(expr->child.left);
            printf(" ");
            show_expr(expr->child.right);
            printf(")");
            break;
        
        case NOT:
            printf("(not ");
            show_expr(expr->child.left);
            if (expr->child.right != NULL) {
                printf(" ");
                show_expr(expr->child.right);
            }
            printf(")");
            break;
            
        case INTEGER:
            printf("%d",expr->number);
            break;
            
        case STRING:
            printf("%s",expr->str);
            break;
            
        case BOOLEAN:
            if (expr->boolean == true) {
                printf("true");
            }
            else {
                printf("false");
            }
            break;
        
        default:
            printf("default");
    }
}

void show_expr_list(expr_list_t *expr_list)
{
    expr_list_t *temp = expr_list;
    while (temp != NULL) {
        printf(" ");
        show_expr(temp->expr);
        
        temp = temp->next;
    }
}

void show_formal_list(formal_list_t *formal_list)
{
    formal_list_t *temp = formal_list;
    while (temp != NULL) {
        printf("%s", temp->formal->id);
        printf("[%s]", temp->formal->type);
        temp = temp->next;
    }
}

void show_feature_list(feature_list_t *feature_list)
{
    feature_list_t *temp = feature_list;
    while (temp != NULL) {
        printf("{");
        printf("%s", temp->feature->id);
        if (strcmp(temp->feature->option, "f")==0){
            printf("(");
            if (temp->feature->formals != NULL) {
                show_formal_list(temp->feature->formals);
            }
            printf(")");
        }
        printf("[%s]", temp->feature->type);
        if (strcmp(temp->feature->option, "a")==0){
            printf("<-");
        }
        if (temp->feature->exprs != NULL) {
            show_expr_list(temp->feature->exprs);
        }
        printf("}");
        temp = temp->next;
    }
}


void show_class_list(class_list_t *class_list)
{
    class_list_t *temp = class_list;
    
    while (temp != NULL) {
        printf("[%s]", temp->class->type);
        if (temp->class->inherited != NULL) {
            printf("[%s]", temp->class->inherited);
        }
        if (temp->class->features != NULL) {
            show_feature_list(temp->class->features);
        }
        printf("\n");
        temp = temp->next;
    }
}



class_t *new_class(char *type, char *inherited, feature_list_t *features)
{
    class_t *class;
    
    class = (class_t *)malloc(sizeof(class_t));
    if (class == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    class->type = type;
    if (inherited != NULL){
        class->inherited = inherited;
    }
    if (features != NULL ){
        class->features = features;
    }
    return class;
}

class_list_t *new_class_list(class_t *class, class_list_t *next)
{
    class_list_t *class_list;
    
    class_list = (class_list_t *)malloc(sizeof(class_list_t));
    if (class_list == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    class_list->class = class;
    class_list->next = next;
    
    return class_list;
}

feature_t *new_feature(char *id, char *type, formal_list_t *formals, expr_list_t *exprs, char *option)
{
    feature_t *feature;
    
    feature = (feature_t *)malloc(sizeof(feature_t));
    if (feature == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    feature->id = id;
    if (type != NULL){
        feature->type = type;
    }
    if (formals != NULL ){
        feature->formals = formals;
    }
    if (exprs != NULL){
        feature->exprs = exprs;
    }
    feature->option = option;
    return feature;
}

feature_list_t *new_feature_list(feature_t *feature, feature_list_t *next)
{
    feature_list_t *feature_list;
    
    feature_list = (feature_list_t *)malloc(sizeof(feature_list_t));
    if (feature_list == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    feature_list->feature = feature;
    feature_list->next = next;
    
    return feature_list;
}

formal_t *new_formal(char *id, char *type)
{
    formal_t *formal;
    
    formal = (formal_t *)malloc(sizeof(formal_t));
    if (formal == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    formal->id = id;
    if (type != NULL){
        formal->type = type;
    }
    
    return formal;
}

formal_list_t *new_formal_list(formal_t *formal, formal_list_t *next)
{
    formal_list_t *formal_list;
    
    formal_list = (formal_list_t *)malloc(sizeof(formal_list_t));
    if (formal_list == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    formal_list->formal = formal;
    formal_list->next = next;
    
    return formal_list;
}

expr_t *new_expr_assign(int type, char *id, expr_t *expr1)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->assign.id = id;
    expr->assign.expr = expr1;
    
    return expr;
}

expr_t *new_number(int number)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = INTEGER;
    expr->number = number;
    return expr;
}

expr_t *new_str(char *str)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = STRING;
    expr->str = str;
    return expr;
}

expr_t *new_new(char *new)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = NEW;
    expr->new = new;
    return expr;
}

expr_t *new_bool(bool boolean)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = BOOLEAN;
    expr->boolean = boolean;
    return expr;
}

expr_t *new_expr(int type, expr_t *left, expr_t *right)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->child.left = left;
    expr->child.right = right;
    
    return expr;
}

expr_t *new_expr_at(int type, char *type_at, char *id, expr_t *first, expr_list_t *exprs)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->at.type = type_at;
    expr->at.id = id;
    expr->at.first = first;
    expr->at.exprs = exprs;
    
    return expr;
}

expr_t *new_expr_dot(int type, char *id, expr_t *first, expr_list_t *exprs)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->at.id = id;
    expr->at.first = first;
    expr->at.exprs = exprs;
    
    return expr;
}

expr_t *new_expr_f(int type, char *id, expr_list_t *exprs)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->at.id = id;
    expr->at.exprs = exprs;
    
    return expr;
}

expr_t *new_expr_if(int type, expr_list_t *exprs1, expr_list_t *exprs2, expr_list_t *exprs3)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->iffi.exprs1 = exprs1;
    expr->iffi.exprs2 = exprs2;
    expr->iffi.exprs3 = exprs3;
    
    return expr;
}

expr_t *new_expr_while(int type, expr_list_t *exprs1, expr_list_t *exprs2)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->whileloop.exprs1 = exprs1;
    expr->whileloop.exprs2 = exprs2;
    
    return expr;
}

expr_t *new_expr_curlybrakets(int type, expr_list_t *exprs)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->curlybrakets.exprs = exprs;
    
    return expr;
}

expr_t *new_expr_let(int type, let_list_t *lets, expr_list_t *exprs)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->let.lets = lets;
    expr->let.exprs = exprs;
    
    return expr;
}

expr_t *new_expr_case(int type, expr_t *expr1, case_id_list_t *cases)
{
    expr_t *expr;
    
    expr = (expr_t *)malloc(sizeof(expr_t));
    if (expr == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr->type = type;
    expr->caseesac.expr = expr1;
    expr->caseesac.cases = cases;
    
    return expr;
}

expr_list_t *new_expr_list(expr_t *expr, expr_list_t *next)
{
    expr_list_t *expr_list;
    
    expr_list = (expr_list_t *)malloc(sizeof(expr_list_t));
    if (expr_list == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    expr_list->expr = expr;
    expr_list->next = next;
    
    return expr_list;
}

let_t *new_let(char *id, char *type, expr_t *expr)
{
    let_t *let;
    
    let = (let_t *)malloc(sizeof(let_t));
    if (let == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    let->id = id;
    let->type = type;
    let->expr = expr;
    
    return let;
}

let_list_t *new_let_list(let_t *let, let_list_t *next)
{
    let_list_t *let_list;
    
    let_list = (let_list_t *)malloc(sizeof(let_list_t));
    if (let_list == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    let_list->let = let;
    let_list->next = next;
    
    return let_list;
}

case_id_t *new_case(char *id, char*type, expr_t *expr)
{
    case_id_t *case_id;
    
    case_id = (case_id_t *)malloc(sizeof(case_id_t));
    if (case_id == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    case_id->id = id;
    case_id->type = type;
    case_id->expr = expr;
    
    return case_id;
}

case_id_list_t *new_case_list(case_id_t *case_id, case_id_list_t *next)
{
    case_id_list_t *case_id_list;
    
    case_id_list = (case_id_list_t *)malloc(sizeof(case_id_list_t));
    if (case_id_list == NULL) {
        printf("out of memory\n");
        exit(1);
    }
    case_id_list->case_id = case_id;
    case_id_list->next = next;
    
    return case_id_list;
}
