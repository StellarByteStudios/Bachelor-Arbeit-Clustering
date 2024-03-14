CC = g++
CFLAGS = -Wall -g #-std=c++14
BINNAME = Fair-Clustering
TESTNAME = Clustering-Test

INPUTFILE = Data/Subsamples/bank/bankSample-0.csv
OUTPUTFOLDER = Data/OutputData/MakefileTest/
OUTPUTFILENAME = ClusterOut.csv
CLUSTERNUM = 5

TESTARGS = $(INPUTFILE) $(OUTPUTFOLDER)$(OUTPUTFILENAME) $(CLUSTERNUM)


HDATEIEN = ColoredPoint.h PointParser.h Gonzalez.h FairlettFinder.h RedCenterClustering.h
CPPSOURCE = ColoredPoint.cpp PointParser.cpp Gonzalez.cpp FairlettFinder.cpp RedCenterClustering.cpp
CPPMAIN = ClusteringMain.cpp $(CPPSOURCE)
CPPTEST = ClusteringTest.cpp $(CPPSOURCE)

LINKLIB = -lemon -L/home/stellarbyte/Installationen/Lemon-Lib/lib
HEADERS = -isystem /home/stellarbyte/Installationen/Lemon-Lib/include

VALFLAGS = --leak-check=full



#run: $(BINNAME)
#	mkdir -p $(OUTPUTFOLDER)
#	./$(BINNAME) $(ARGS)

#$(BINNAME): $(HDATEIEN) $(CPPDATEIEN)
#	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPDATEIEN) $(LINKLIB) $(HEADERS)
	
build: $(HDATEIEN) $(CPPMAIN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPMAIN) $(LINKLIB) $(HEADERS)

runTest: $(TESTNAME)
	./$(TESTNAME) $(TESTARGS)

$(TESTNAME): $(HDATEIEN) $(CPPTEST)
	$(CC) $(CFLAGS) -o $(TESTNAME) $(CPPTEST) $(LINKLIB) $(HEADERS)

val: $(TESTNAME)
	valgrind $(VALFLAGS) ./$(TESTNAME) $(TESTARGS) 




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
	
