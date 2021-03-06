#Teddy Vallar
#makefile

# Defines the C++ compiler
CXX	= g++

# Defines the flags for C++
CXXFLAGS	= -Wall


# All of the .o files for our program
OFILES	= main.o Word.o Dictionary.o Neuron.o Net.o InputHandler.o


.SUFFIXES: .o .cpp



main:	$(OFILES)
	$(CXX) $(CXXFLAGS) $(OFILES)


clean:
	/bin/rm -f *.o *~


