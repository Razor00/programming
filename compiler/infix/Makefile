tgt = infix
all: $(tgt)

infix: lex.yy.c y.tab.c
		gcc $^ -o $@


lex.yy.c: infix.lex
		flex $<
	
y.tab.c:  infix.y
		bison -d -y $<

clean:
	rm -f *.c *.h  $(tgt)
