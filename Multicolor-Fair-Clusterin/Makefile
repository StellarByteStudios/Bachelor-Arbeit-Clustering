CC = g++
CFLAGS = -Wall -g
NAME = Fair-Clustering
ARGS = Data/RandomGenerated/Points2D.txt Data/OutputData/PathTesting/ClusterOut2DPath.csv 4
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
	
