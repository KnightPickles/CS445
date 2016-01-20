BIN  = c-
CC   = g++
SRCS = $(BIN).y $(BIN).l tokenClass.h globals.h util.h util.c
OBJS = lex.yy.o $(BIN).tab.o util.o
LIBS = -lm 

$(BIN): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) $(LIBS) -o $(BIN)

$(BIN).tab.h $(BIN).tab.c: $(BIN).y
	bison -v -t -d $(BIN).y   # -d supplies defines file

lex.yy.c: $(BIN).l $(BIN).tab.h
	flex $(BIN).l  # -d debug

util.o: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c


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
	tar -cvf $(BIN).tar $(SRCS) makefile 

