BIN = parser
CC = g++
OUT = c-
LIBS = ourgetopt.h ast.h exp.h stmt.h var.h fun.h semantic.h printtree.h symbolTable.h yyerror.h emitcode.h scanType.h
FLAGS = -g `llvm-config --cxxflags --ldflags --system-libs --libs core`
OBJS = ourgetopt.o ast.o exp.o stmt.o var.o fun.o semantic.o printtree.o symbolTable.o yyerror.o emitcode.o

.PHONY : all tar clean tm

all : lex.yy.c $(BIN).tab.c $(BIN).tab.h $(LIBS) $(OBJS)
	$(CC) $(FLAGS) lex.yy.c $(BIN).tab.c $(OBJS) -o $(OUT)

$(BIN).tab.c $(BIN).tab.h : $(BIN).y $(LIBS)
	bison -v -t -d $(BIN).y

lex.yy.c : $(BIN).l $(BIN).tab.h scanType.h
	flex $(BIN).l

%.o: %.cpp $(LIBS)
	$(CC) $(FLAGS) -c $<

tm :
	$(CC) $(FLAGS) -o tm tm.c

tar :
	tar -cvf $(BIN).tar $(BIN).y $(BIN).l Makefile *.cpp *.h

clean :
	rm $(BIN).tab.c $(BIN).tab.h lex.yy.c $(OUT) $(BIN).output *.o $(BIN).tar
