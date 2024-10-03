
CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

ast: y.tab.o lex.yy.o ast.o
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o ast.o -o ast 

ast.o: ast.cpp ast.h
	${CCC} -c ast.cpp

y.tab.o: parser.yacc
	${YACC} ${YFLAGS} parser.yacc
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: scanner.lex
	${LEX} $(LFLAGS) scanner.lex
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o ast
