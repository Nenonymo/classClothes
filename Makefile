# Makefile written by Nemo chentre, Umea University and University cote-d'azur

SRC = ./src/c
INC = ./include
TOOL = ./tools

TARGET = labeller

OBJS = $(SRC)/wavelet.o \
       $(TOOL)/fileSyst.o \
	   $(SRC)/pythonEmbedding.o \
       $(SRC)/preprocessor.o \
       $(SRC)/processesManagement.o \
       $(SRC)/main.o

CXX = g++

#Compiler flags
DBFLAGS = -O2
WFLAGS = -Wall -std=c++11 #Wall flag 

#OpenCV Flags
CVFLAGS = `pkg-config --cflags opencv4`
LCVFLAGS = `pkg-config --libs opencv4`

#Include & local libs flags
IFLAGS = -I${INC} -I${TOOL}
LFLAGS = -lstdc++ -fopenmp

#Compiling flags
CXXFLAGS = ${DBFLAGS} ${WFLAGS} ${IFLAGS} ${CVFLAGS} ${LFLAGS}
LDFLAGS = $(LCVFLAGS)

all: $(TARGET)
clean:
	rm -f $(OBJS) $(TARGET)

.SUFFIXES: .o .c .cpp .cxx .cc
.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"
.cxx.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"
.cc.o:
	$(CXX) -c $(CXXFLAGS) $<
.c.o:
	$(CXX) -c $(CXXFLAGS) $<
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)
