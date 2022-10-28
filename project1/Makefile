#
# Copyright 2020-2022. Heekuck Oh, all rights reserved
# 이 파일은 한양대학교 ERICA 소프트웨어학부 재학생을 위해 만들었다.
#
CC = gcc
CFLAGS = -Wall -O3
CLIBS = -ll
#
OS := $(shell uname -s)
ifeq ($(OS), Linux)
#	CLIBS +=
endif
ifeq ($(OS), Darwin)
	CLIBS += -mmacosx-version-min=12.3
endif
#
all: lex.yy.o
	$(CC) -o cool_lexer lex.yy.o $(CLIBS)

lex.yy.o: cool.l cool.tab.h
	flex cool.l
	$(CC) $(CFLAGS) -c lex.yy.c

clean:
	rm -rf *.o
	rm -rf cool_lexer
	rm -rf lex.yy.c
