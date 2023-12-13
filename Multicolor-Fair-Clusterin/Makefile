CC = g++
CFLAGS = -Wall -g
NAME = Fair-Clustering
ARGS = Data/RandomGenerated/Points2D.txt Data/OutputData/PathTesting/ClusterOut2DPath.csv
#PX = ../../
#HDATEIEN = $(PX)ColoredPoint.h $(PX)PointParser.h
#CPPDATEIEN = $(PX)ClusteringMain.cpp $(PX)ColoredPoint.cpp $(PX)PointParser.cpp
HDATEIEN = ColoredPoint.h PointParser.h Gonzales.h
CPPDATEIEN = ClusteringMain.cpp ColoredPoint.cpp PointParser.cpp Gonzales.cpp




all: $(NAME)
	./$(NAME) $(ARGS)

$(NAME): $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN)
	
build: $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN)

# noch mit Headderdateien
#$(NAME): $(HDATEIEN) $(CPPDATEIEN)
#	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN) $(HDATEIEN)

val: $(NAME)
	valgrind ./$(NAME) $(ARGS)
	
