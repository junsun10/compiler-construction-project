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
	# CLIBS += -mmacosx-version-min=12.3
	CLIBS += -mmacosx-version-min=13.0
endif
#
all: lex.yy.o cool.tab.o node.o
	$(CC) -o cool_parser lex.yy.o cool.tab.o node.o $(CLIBS)

cool.tab.h cool.tab.c: cool.y node.h
	bison -d cool.y
	
cool.tab.o: cool.tab.h cool.tab.c
	$(CC) $(CFLAGS) -c cool.tab.c

lex.yy.o: cool.l cool.tab.h node.h
	flex cool.l
	$(CC) $(CFLAGS) -c lex.yy.c

node.o: node.h node.c
	$(CC) $(CFLAGS) -c node.c
	
clean:
	rm -rf *.o
	rm -rf cool_parser
	rm -rf cool.tab.c cool.tab.h lex.yy.c
