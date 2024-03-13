CC = g++
CFLAGS = -Wall -g #-std=c++14
LINKLIB = -lemon -L/home/stellarbyte/Installationen/Lemon-Lib/lib
HEADERS = -I/home/stellarbyte/Installationen/Lemon-Lib/include


libtest: LemonLibTest.cpp
	$(CC) $(CFLAGS) -o LibTest LemonLibTest.cpp $(LINKLIB) $(HEADERS)
	./LibTest

maxFlowTest: MaxFlowTest.cpp
	$(CC) $(CFLAGS) -o MaxFlowTest MaxFlowTest.cpp $(LINKLIB) $(HEADERS)
	./MaxFlowTest
	
fairlettTest: FairlettBuildupTest.cpp FairlettBuildupTest.h
	$(CC) $(CFLAGS) -o FairlettBuildupTest FairlettBuildupTest.cpp $(LINKLIB) $(HEADERS)
	./FairlettBuildupTest