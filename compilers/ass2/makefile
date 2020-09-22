BIN = parser
CC = g++
OUT = c-
INCLUDES = ourgetopt.h ast.h scanType.h
FLAGS = -DCPLUSPLUS -g
LIBS = ourgetopt.cpp ast.cpp

$(BIN) : lex.yy.c $(BIN).tab.c $(BIN).tab.h $(INCLUDES)
	$(CC) $(FLAGS) lex.yy.c $(BIN).tab.c $(LIBS) -o $(OUT)

$(BIN).tab.c $(BIN).tab.h : $(BIN).y $(INCLUDES)
	bison -v -t -d $(BIN).y

lex.yy.c : $(BIN).l $(BIN).tab.h scanType.h
	flex $(BIN).l

run :
	cat test.c- | ./$(OUT) -p

tar :
	tar -cvf $(BIN).tar $(BIN).y $(BIN).l $(INCLUDES) $(LIBS) makefile

clean :
	rm $(BIN).tab.c $(BIN).tab.h lex.yy.c $(OUT) $(BIN).output
