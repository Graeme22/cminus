BIN = parser
CC = g++
OUT = c-
LIBS = ourgetopt.h
FLAGS = -DCPLUSPLUS -g

$(BIN) : lex.yy.c $(BIN).tab.c $(BIN).tab.h $(LIBS)
	$(CC) $(FLAGS) lex.yy.c $(BIN).tab.c ourgetopt.cpp -o $(OUT)

$(BIN).tab.c $(BIN).tab.h : $(BIN).y scanType.h $(LIBS)
	bison -v -t -d $(BIN).y

lex.yy.c : $(BIN).l $(BIN).tab.h scanType.h
	flex $(BIN).l

run :
	cat test.c- | ./$(OUT) -p

tar :
	tar -cvf $(BIN).tar $(BIN).y $(BIN).l scanType.h makefile ourgetopt.*

clean :
	rm $(BIN).tab.c $(BIN).tab.h lex.yy.c $(OUT) $(BIN).output
