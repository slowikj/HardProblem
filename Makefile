FLAGS= -std=c++11 -Wall

all:
	g++ ${FLAGS} PrefixInfo.cpp PrefixResultComputer.cpp ReversableString.cpp TaskData.cpp TaskSolver.cpp main.cpp -o main

