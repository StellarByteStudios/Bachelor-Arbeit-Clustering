CC = g++
CFLAGS = -Wall -g #-std=c++14
BINNAME = Fair-Clustering
TESTNAME = Clustering-Test

INPUTFILE = Data/Subsamples/bank/bankSample-0.csv
OUTPUTFOLDER = Data/OutputData/MakefileTest/
OUTPUTFILENAME = ClusterOut2.csv
CLUSTERNUM = 15

TESTARGS = $(INPUTFILE) $(OUTPUTFOLDER)$(OUTPUTFILENAME) $(CLUSTERNUM)


HDATEIEN = ColoredPoint.h PointParser.h Gonzalez.h FairlettFinder.h RedCenterClustering.h GraphFlow.h
CPPSOURCE = ColoredPoint.cpp PointParser.cpp Gonzalez.cpp FairlettFinder.cpp RedCenterClustering.cpp GraphFlow.cpp

FASTHDATEIEN = FastAnchorClustering.h FastAnchorFairlett.h FastAnchorFlow.h
FASTSOURCE = FastAnchorClustering.cpp FastAnchorFairlett.cpp FastAnchorFlow.cpp

CPPMAIN = ClusteringMain.cpp $(CPPSOURCE) $(FASTSOURCE)
CPPTEST = ClusteringTest.cpp $(CPPSOURCE) $(FASTSOURCE)

LINKLIB = -lemon -L/home/stellarbyte/Installationen/Lemon-Lib/lib
HEADERS = -isystem /home/stellarbyte/Installationen/Lemon-Lib/include

VALFLAGS = --leak-check=full

# Preprocessor-Flags
PROCESSBAR = -DPROCESS_BAR



#run: $(BINNAME)
#	mkdir -p $(OUTPUTFOLDER)
#	./$(BINNAME) $(ARGS)

#$(BINNAME): $(HDATEIEN) $(CPPDATEIEN)
#	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPDATEIEN) $(LINKLIB) $(HEADERS)
	
build: $(HDATEIEN) $(FASTHDATEIEN) $(CPPMAIN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPMAIN) $(LINKLIB) $(HEADERS)

buildProcessBar: $(HDATEIEN) $(FASTHDATEIEN) $(CPPMAIN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPMAIN) $(LINKLIB) $(HEADERS) $(PROCESSBAR)

runTest: $(TESTNAME)
	./$(TESTNAME) $(TESTARGS)

$(TESTNAME): $(HDATEIEN) $(FASTHDATEIEN) $(CPPTEST)
	$(CC) $(CFLAGS) -o $(TESTNAME) $(CPPTEST) $(LINKLIB) $(HEADERS)

val: buildTestProcess
	valgrind $(VALFLAGS) ./$(TESTNAME) $(TESTARGS) 


buildTestProcess: $(HDATEIEN) $(FASTHDATEIEN) $(CPPTEST)
	$(CC) $(CFLAGS) -o $(TESTNAME) $(CPPTEST) $(LINKLIB) $(HEADERS) $(PROCESSBAR)

runTestProcess: buildTestProcess
	./$(TESTNAME) $(TESTARGS) 

testAutofeeder: $(HDATEIEN) $(FASTHDATEIEN) $(CPPMAIN)
	/bin/bash ./AlgFeeder.sh -i $(INPUTFILE) -o $(OUTPUTFOLDER) -n $(OUTPUTFILENAME) -c $(CLUSTERNUM) -a r


printVar: Makefile

#	echo "CC: $(CC)"
#	echo "CFLAGS: $(CFLAGS)"
#	echo "BINNAME: $(BINNAME)"
#	echo "INPUTFILE: $(INPUTFILE)"
#	echo "OUTPUTFOLDER: $(OUTPUTFOLDER)"
#	echo "OUTPUTFILENAME: $(OUTPUTFILENAME)"
#	echo "CLUSTERNUM: $(CLUSTERNUM)"
	echo "ARGS: $(ARGS)"
#	echo "HDATEIEN: $(HDATEIEN)"
#	echo "CPPDATEIEN: $(CPPDATEIEN)" 
	
