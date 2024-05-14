# # # Everything for compiling
CC = g++
CFlags = -Wall -g #-std=c++14
BinName = Fair-Clustering
TestBinName = Clustering-Test


# # # Some Test Arguments
InputFile = Data/Subsamples/bank/bankSample-0.csv
TestOutputFolder = Data/OutputData/MakefileTest/
TestOutputFileName = ClusterOut2.csv
ClusterNum = 4

TestArgs = $(InputFile) $(TestOutputFolder)$(TestOutputFileName) $(ClusterNum)

# # # All Files to be Included
# Source-directory if different from building direktory
srcdir = ./src

# Points
folderPoints = $(srcdir)/Points/
hFilesPoints = $(folderPoints)ColoredPoint.h $(folderPoints)PointParser.h
cppFilesPoints = $(folderPoints)ColoredPoint.cpp $(folderPoints)PointParser.cpp

# Gonzalez
folderGonzalez = $(srcdir)/Gonzalez/
hFilesGonzalez = $(folderGonzalez)Gonzalez.h
cppFilesGonzalez = $(folderGonzalez)Gonzalez.cpp

# RedClustering
folderRedClustering = $(srcdir)/RedClustering/
hFilesRedClustering = $(folderRedClustering)FairlettFinder.h $(folderRedClustering)RedCenterClustering.h $(folderRedClustering)GraphFlow.h
cppFilesRedClustering = $(folderRedClustering)FairlettFinder.cpp $(folderRedClustering)RedCenterClustering.cpp $(folderRedClustering)GraphFlow.cpp

# FastClustering
folderFastClustering = $(srcdir)/FastAnchorClustering/
hFilesFastClustering = $(folderFastClustering)FastAnchorClustering.h $(folderFastClustering)FastAnchorFairlett.h $(folderFastClustering)FastAnchorFlow.h
cppFilesFastClustering = $(folderFastClustering)FastAnchorClustering.cpp $(folderFastClustering)FastAnchorFairlett.cpp $(folderFastClustering)FastAnchorFlow.cpp


# Alle SourceDateien zusammensetzen
hFiles = $(hFilesPoints) $(hFilesGonzalez) $(hFilesRedClustering) $(hFilesFastClustering)
cppFiles = $(cppFilesPoints) $(cppFilesGonzalez) $(cppFilesRedClustering) $(cppFilesFastClustering)

# Befehle für Main oder Test
cppMain = $(srcdir)/ClusteringMain.cpp $(cppFiles)
cppTest = $(srcdir)/ClusteringTest.cpp $(cppFiles)


# # # Bibliothek Flags
linkLemonLib = -lemon -L/home/stellarbyte/Installationen/Lemon-Lib/lib
lemonLibHeadder = -isystem /home/stellarbyte/Installationen/Lemon-Lib/include


# # # Flags für Valgrind
ValFlags = --leak-check=full

# # # Preprocessor-Flags
Processbar = -DPROCESS_BAR



	
build: $(hFiles) $(cppMain)
	$(CC) $(CFlags) -o $(BinName) $(cppMain) $(linkLemonLib) $(lemonLibHeadder)

buildProcessBar: $(hFiles) $(cppMain)
	$(CC) $(CFlags) -o $(BinName) $(cppMain) $(linkLemonLib) $(lemonLibHeadder) $(Processbar)

runTest: $(TestBinName)
	./$(TestBinName) $(TestArgs)

$(TestBinName): $(hFiles) $(cppTest)
	$(CC) $(CFlags) -o $(TestBinName) $(cppTest) $(linkLemonLib) $(lemonLibHeadder)

val: buildTestProcess
	valgrind $(ValFlags) ./$(TestBinName) $(TestArgs) 


buildTestProcess: $(hFiles) $(cppTest)
	$(CC) $(CFlags) -o $(TestBinName) $(cppTest) $(linkLemonLib) $(lemonLibHeadder) $(Processbar)

runTestProcess: buildTestProcess
	./$(TestBinName) $(TestArgs) 

testAutofeeder: $(hFiles) $(cppMain)
	/bin/bash ./AlgFeeder.sh -i $(InputFile) -o $(TestOutputFolder) -n $(TestOutputFileName) -c $(ClusterNum) -a r


printVar: Makefile

#	echo "CC: $(CC)"
#	echo "CFlags: $(CFlags)"
#	echo "BinName: $(BinName)"
#	echo "InputFile: $(InputFile)"
#	echo "TestOutputFolder: $(TestOutputFolder)"
#	echo "TestOutputFileName: $(TestOutputFileName)"
#	echo "ClusterNum: $(ClusterNum)"
	echo "TestArgs: $(TestArgs)"
#	echo "hFiles: $(hFiles)"
#	echo "cppFiles: $(cppFiles)" 
	
