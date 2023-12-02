CC = g++
CFLAGS = -Wall -g
NAME = Fair-Clustering
#PX = ../../
#HDATEIEN = $(PX)ColoredPoint.h $(PX)PointParser.h
#CPPDATEIEN = $(PX)ClusteringMain.cpp $(PX)ColoredPoint.cpp $(PX)PointParser.cpp
HDATEIEN = ColoredPoint.h PointParser.h Gonzales.h
CPPDATEIEN = ClusteringMain.cpp ColoredPoint.cpp PointParser.cpp Gonzales.cpp




all: $(NAME)
	./$(NAME)

$(NAME): $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN)
	
build: $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN)

# noch mit Headderdateien
#$(NAME): $(HDATEIEN) $(CPPDATEIEN)
#	$(CC) $(CFLAGS) -o $(NAME) $(CPPDATEIEN) $(HDATEIEN)

val: $(NAME)
	valgrind ./$(NAME) 
	
