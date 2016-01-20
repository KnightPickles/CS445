BIN  = c-
CC   = g++
SRCS = $(BIN).y $(BIN).l token.h globals.h util.h util.cpp semantics.h semantics.cpp emit.h emit.cpp codegen.h codegen.cpp symbolTable.h symbolTable.cpp
OBJS = lex.yy.o $(BIN).tab.o util.o semantics.o emit.o codegen.o symbolTable.o 
LIBS = -lm 

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y   # -d supplies defines file

lex.yy.c: $(BIN).l $(BIN).tab.h 
	flex $(BIN).l  # -d debug

util.o: util.cpp util.h globals.h
	$(CC) $(CFLAGS) -c util.cpp

semantics.o: semantics.h semantics.cpp globals.h symbolTable.o
	$(CC) $(CFLAGS) -c semantics.cpp

codegen.o: codegen.h codegen.cpp globals.h symbolTable.o emit.o
	$(CC) $(CFLAGS) -c codegen.cpp

emit.o: emit.h emit.cpp
	$(CC) $(CFLAGS) -c emit.cpp

symbolTable.o: symbolTable.h symbolTable.cpp
	$(CC) $(CFLAGS) -c symbolTable.cpp


all:    
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) $(BIN).output lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~

pdf:	
	c-.y c-.l makefile
	mktex c-.y
	mv c-.pdf c--y.pdf
	mktex c-.l
	mv c-.pdf c--l.pdf
	mktex makefile
	save c--l.pdf c--y.pdf makefile.pdf
	rm *.tex

tar:
	tar -cvf $(BIN).tar $(SRCS) makefile 

