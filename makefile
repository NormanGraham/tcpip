
.PHONY: all
all: xy_tcpip.o

xy_tcpip.o : xy_tcpip.cpp 
   g++ -o xy_tcpip.o -g -c xy_tcpip.cpp 
   
