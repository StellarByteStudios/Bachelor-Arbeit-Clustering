CC = g++
CFLAGS = -Wall -g
NAME = Fair-Clustering
INPUTFILE = Data/Subsamples/bank/bankSample-0.csv
OUTPUTFILE = Data/OutputData/MakefileTest/ClusterOut.csv
CLUSTERNUM = 5
ARGS = $(INPUTFILE) $(OUTPUTFILE) $(CLUSTERNUM)
HDATEIEN = ColoredPoint.h PointParser.h Gonzalez.h
CPPDATEIEN = ClusteringMain.cpp ColoredPoint.cpp PointParser.cpp Gonzalez.cpp




all: $(NAME)
	./$(NAME) $(ARGS)

$(NAME): $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN)
	
build: $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN)


val: $(NAME)
	valgrind ./$(NAME) $(ARGS)
	
