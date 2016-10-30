all: storm.tab.c storm.tab.h lex.yy.c storm

storm.tab.c storm.tab.h: storm.y
	bison -d storm.y
lex.yy.c: storm.l storm.tab.h
	flex storm.l
storm: lex.yy.c storm.tab.c storm.tab.h
	g++ -std=gnu++0x storm.tab.c lex.yy.c -o storm
