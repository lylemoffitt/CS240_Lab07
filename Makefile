FLAGS = -g -std=c++0x
COMPILER = g++
OUTPUT_NAME = submission

all: Lab07.o Driver07.o
	$(COMPILER) $(FLAGS) -o $(OUTPUT_NAME) Lab07.o Driver07.o

Lab07.o : Lab07.cpp
	$(COMPILER) $(FLAGS) -c Lab07.cpp

Driver07.o : Driver07.cpp
	$(COMPILER) $(FLAGS) -c Driver07.cpp

clean:
	rm -rf *.o $(OUTPUT_NAME)

