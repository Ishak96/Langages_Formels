all:ess

ess: y.tab.o lex.yy.o
	cc -o ess y.tab.o lex.yy.o -lfl

y.tab.o: y.tab.c
	cc -c y.tab.c

lex.yy.o: lex.yy.c
	cc -c lex.yy.c

y.tab.c: ess.y
	yacc -d ess.y

lex.yy.c: ess.l y.tab.h
	flex ess.l

y.tab.h: ess.y
	yacc -d ess.y

clean:
	rm -f y.tab.* lex.yy.* ess
