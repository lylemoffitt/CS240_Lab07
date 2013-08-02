COMPILER = g++
FLAGS = -g -std=c++0x
OUTPUT_NAME = submission

all: Lab07.cpp Driver.cpp
	$(COMPILER) -Wall $(FLAGS) -o $(OUTPUT_NAME) Lab07.cpp Driver.cpp

Lab07.o : Lab07.cpp
	$(COMPILER) -Wall $(FLAGS) -c Lab07.cpp

Driver.o : Driver.cpp
	$(COMPILER) -Wall $(FLAGS) -c Driver.cpp

clean:
	rm -rf *.o $(OUTPUT_NAME)

