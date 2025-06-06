CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall

SRC = src/QuizGame.cpp
HEADERS = include/QuizGame.h include/Question.h

all: main1 main2

main1: main1.cpp $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o bin/main1 main1.cpp $(SRC)

main2: main2.cpp $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o bin/main2 main2.cpp $(SRC)

clean:
	del /Q bin\main1.exe bin\main2.exe
