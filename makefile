CC=g++
CFLAGS=-Wall -std=c++17 -o
BINS= S1 S2
all: S1 S2

S1:
	$(CC) $(CFLAGS) demostracion1 demostracion1.cpp

S2:
	$(CC) $(CFLAGS) demostracion2 demostracion2.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)