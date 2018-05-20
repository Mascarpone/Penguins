CFLAGS = -std=c99 -Wall -pedantic
LFLAGS = -shared -fPIC -undefined dynamic_lookup # for MAC OS -undefined dynamic_lookup
CXX = gcc

all: libCNE randflo superflo

libCNE:
	$(CXX) $(CFLAGS) $(LFLAGS) -o libCNE.so ../src/clients/CNEPonder.c

randflo:
	$(CXX) $(CFLAGS) $(LFLAGS) -o randflo.so ../src/clients/Randflo.c

superflo:
	$(CXX) $(CFLAGS) $(LFLAGS) -o superflo.so ../src/clients/Superflo.c

clean:
	rm -rf *.so
