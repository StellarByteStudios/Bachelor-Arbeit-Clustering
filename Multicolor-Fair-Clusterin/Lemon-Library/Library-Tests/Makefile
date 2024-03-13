CC = g++
CFLAGS = -Wall -g #-std=c++14
LINKLIB = -llemon #-LLemon-Libary/lemon-1.3.1-build/


libtest: Lemon-Libary/lemon-1.3.1-build/liblemon.a LemonLibTest.cpp
	$(CC) $(CFLAGS) -o LibTest LemonLibTest.cpp $(LINKLIB)
	./LibTest

maxFlowTest: Lemon-Libary/lemon-1.3.1-build/liblemon.a MaxFlowTest.cpp
	$(CC) $(CFLAGS) -o MaxFlowTest MaxFlowTest.cpp $(LINKLIB)
	./MaxFlowTest
	
fairlettTest: Lemon-Libary/lemon-1.3.1-build/liblemon.a FairlettBuildupTest.cpp FairlettBuildupTest.h
	$(CC) $(CFLAGS) -o FairlettBuildupTest FairlettBuildupTest.cpp $(LINKLIB)
	./FairlettBuildupTest