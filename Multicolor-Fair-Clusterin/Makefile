CC = g++
CFLAGS = -Wall -g #-std=c++14
BINNAME = Fair-Clustering

INPUTFILE = Data/Subsamples/bank/bankSample-0.csv
OUTPUTFOLDER = Data/OutputData/MakefileTest/
OUTPUTFILENAME = ClusterOut.csv
CLUSTERNUM = 5

ARGS = $(INPUTFILE) $(OUTPUTFOLDER)$(OUTPUTFILENAME) $(CLUSTERNUM)


HDATEIEN = ColoredPoint.h PointParser.h Gonzalez.h FairlettFinder.h RedCenterClustering.h
CPPDATEIEN = ClusteringMain.cpp ColoredPoint.cpp PointParser.cpp Gonzalez.cpp FairlettFinder.cpp RedCenterClustering.cpp

LINKLIB = -lemon -L/home/stellarbyte/Installationen/Lemon-Lib/lib
HEADERS = -isystem /home/stellarbyte/Installationen/Lemon-Lib/include

VALFLAGS = --leak-check=full



run: $(BINNAME)
	mkdir -p $(OUTPUTFOLDER)
	./$(BINNAME) $(ARGS)

$(BINNAME): $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPDATEIEN) $(LINKLIB) $(HEADERS)
	
build: $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(BINNAME) $(CPPDATEIEN)


val: $(BINNAME)
	valgrind $(VALFLAGS) ./$(BINNAME) $(ARGS) 




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
	
