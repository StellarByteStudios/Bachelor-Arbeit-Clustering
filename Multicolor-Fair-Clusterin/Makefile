CC = g++
CFLAGS = -Wall -g
BINNAME = Fair-Clustering

INPUTFILE = Data/Subsamples/bank/bankSample-0.csv
OUTPUTFOLDER = Data/OutputData/MakefileTest/
OUTPUTFILENAME = ClusterOut.csv
CLUSTERNUM = 5
ARGS = $(INPUTFILE) $(OUTPUTFOLDER)$(OUTPUTFILENAME) $(CLUSTERNUM)


HDATEIEN = ColoredPoint.h PointParser.h Gonzalez.h
CPPDATEIEN = ClusteringMain.cpp ColoredPoint.cpp PointParser.cpp Gonzalez.cpp

LINKLIB = -LLemon-Libary/lemon-1.3.1-build/ -llemon




all: $(BINNAME)
	mkdir -p $(OUTPUTFOLDER)
	./$(BINNAME) $(ARGS)

$(BINNAME): $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPDATEIEN)
	
build: $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPDATEIEN)


val: $(BINNAME)
	valgrind ./$(BINNAME) $(ARGS)


libtest: Lemon-Libary/lemon-1.3.1-build/liblemon.a LemonLibTest.cpp
	$(CC) $(CFLAGS) -o LibTest LemonLibTest.cpp $(LINKLIB)
	./LibTest






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
	
