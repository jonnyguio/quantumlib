CC = g++
CFLAGS = -Wall -std=c+11
MAIN = main.out
SRCS = sources/complex.cpp sources/matrix.cpp sources/quantumMath.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: depend clean

all: $(MAIN)
	@echo "Simple compiler named mycc has been compiled"

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) */*.o *~ $(MAIN)

depend: $(SRCS)
	makedepend $(INCLUDES) $^
