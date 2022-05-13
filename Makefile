.PHONY: clean
CC?=clang
LD=${CC}
CFLAGS=-g -lm  -Wall  -O3 -Wunused-parameter -Wpointer-arith 
LDFLAGS=-g -lm

# generic compilation rule which creates dependency file on the fly
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) -MT $@ -MMD -MP -MF $(@:.o=.d)

# This is the programm which constructs the huffman code and outputs it
perceptron: main.o
	${LD} $^ -o $@ ${LDFLAGS}

clean:
	${RM} *.[oxd] *~ perceptron
	${RM} -r *.x.dSYM/


