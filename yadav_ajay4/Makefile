# Makefile for p1

# Makefile for a C++ program

# Specify the object file(s)
OBJS=hw5_Ajay_Yadav.o

# Compiler
CC=g++

# Debug flag
DEBUG=-g

# Compiler flags
CFLAGS=-Wall -c $(DEBUG)

# Linker flags
LFLAGS=-Wall $(DEBUG)

# Target for building executable
exe: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o exe

# Compile the source file(s) into object file(s)
hw5_Ajay_Yadav.o: hw5_Ajay_Yadav.cpp
	$(CC) $(CFLAGS) hw5_Ajay_Yadav.cpp

# Clean up object files and executable
clean:
	\rm *.o *~ exe

