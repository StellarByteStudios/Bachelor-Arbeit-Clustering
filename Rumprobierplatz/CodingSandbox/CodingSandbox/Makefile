# Variablen
CC = g++
CFLAGS = -Wall
NAME = PointCLustering
HDATEIEN = BetterReader.h ColoredPoint.h PointParser.h Printer.h Reader.h
CPPDATEIEN = CodingSandbox.cpp BetterReader.cpp ColoredPoint.cpp PointParser.cpp Printer.cpp Reader.cpp

$(NAME): $(HDATEIEN) $(CPPDATEIEN)
	$(CC) $(CFLAGS) -o $(NAME) $(HDATEIEN) $(CPPDATEIEN) 

run: $(NAME)
	./$(NAME)

clean:
	rm -r *o