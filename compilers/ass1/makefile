BIN = parser
CC = g++
OUT = c-
FLAGS = -DCPLUSPLUS -g

$(BIN) : lex.yy.c $(BIN).tab.c $(BIN).tab.h
	$(CC) $(FLAGS) lex.yy.c $(BIN).tab.c -o $(OUT)

$(BIN).tab.c $(BIN).tab.h : $(BIN).y scanType.h
	bison -v -t -d $(BIN).y

lex.yy.c : $(BIN).l $(BIN).tab.h scanType.h
	flex $(BIN).l

run :
	(./$(OUT) < test/everything04.c-) > output.txt

tar :
	tar -cvf $(BIN).tar $(BIN).y $(BIN).l scanType.h makefile

clean :
	rm $(BIN).tab.c $(BIN).tab.h lex.yy.c $(OUT) $(BIN).output output.txt
