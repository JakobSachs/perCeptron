.PHONY: clean
CC?=gcc
LD=${CC}
CFLAGS=-g -lm  -Wall -O3 -fopenmp 
LDFLAGS=-g -lm

# generic compilation rule which creates dependency file on the fly
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) -MT $@ -MMD -MP -MF $(@:.o=.d)

perceptron: main.o
	${LD} $^ -o $@ ${LDFLAGS}

clean:
	${RM} *.[oxd] *~ perceptron
	${RM} -r *.x.dSYM/


