# Project: TerCanvas
# Makefile created by Michael Bittencourt

CPP = g++
CC = gcc
CXX_SOURCES = $(wildcard *.cpp)
OBJ = main.o terCanvas.o graph.o
BIN = terCanvas
CXXFLAGS = -std=c++11
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN)

%.o: %.cpp
	$(CPP) -c $^ -o $@ $(CXXFLAGS)
