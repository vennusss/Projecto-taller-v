CC=g++
CFLAGS=-Wall -std=c++17 -o
BINS= demostracion1 demostracion2 demostracion3
all: S1 S2 S3

S1:
	$(CC) $(CFLAGS) demostracion1 demostracion1.cpp

S2:
	$(CC) $(CFLAGS) demostracion2 demostracion2.cpp

S3:
	$(CC) $(CFLAGS) demostracion3 demostracion3.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)