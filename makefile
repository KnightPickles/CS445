BIN  = c-
CC   = g++
SRCS = $(BIN).y $(BIN).l
OBJS = lex.yy.o $(BIN).tab.o
LIBS = -lm 

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y   # -d supplies defines file

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l  # -d debug

all:    
	touch $(SRCS)
	make

clean:
	rm -f $(OBJS) $(BIN) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).tar *~

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
	tar -cvf $(BIN).tar $(SRCS) makefile tokenClass.h

