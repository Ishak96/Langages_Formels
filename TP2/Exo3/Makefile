all:calc

calc: y.tab.o lex.yy.o
	cc -o calc y.tab.o lex.yy.o -lfl -lm

y.tab.o: y.tab.c
	cc -c y.tab.c -lm

lex.yy.o: lex.yy.c
	cc -c lex.yy.c -lm

y.tab.c: calc.y
	yacc -d calc.y

lex.yy.c: calc.l y.tab.h
	flex calc.l

y.tab.h: calc.y
	yacc -d calc.y

clean:
	rm -f y.tab.* lex.yy.* calc
