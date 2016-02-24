CC = g++
CFLAGS = -Wall -std=c+11
MAIN = main.out
SRCS = sources/complex.cpp sources/quantumRegister.cpp sources/quantumOperator.cpp sources/quantumCircuit.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(MAIN)
	@echo "Compilation of quantumlib completed."

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o */*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
# DO NOT DELETE

sources/complex.o: headers/complex.h headers/constants.h headers/matrix.h
sources/quantumRegister.o: headers/complex.h headers/constants.h
sources/quantumRegister.o: headers/matrix.h headers/quantumRegister.h
sources/quantumOperator.o: headers/complex.h headers/constants.h
sources/quantumOperator.o: headers/matrix.h headers/quantumRegister.h
sources/quantumOperator.o: headers/quantumOperator.h
sources/quantumCircuit.o: headers/complex.h headers/constants.h
sources/quantumCircuit.o: headers/matrix.h headers/quantumRegister.h
sources/quantumCircuit.o: headers/quantumOperator.h headers/quantumCircuit.h
main.o: headers/complex.h headers/constants.h headers/matrix.h
main.o: headers/complex.h headers/quantumRegister.h headers/matrix.h
main.o: headers/quantumOperator.h headers/quantumRegister.h
main.o: headers/quantumCircuit.h headers/quantumOperator.h circuits.h
