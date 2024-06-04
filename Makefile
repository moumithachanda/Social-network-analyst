CC = g++
CFLAGS = -O3 -std=c++17
TARG = network
 
DEPS = main.o graph.o user_account.o

$(TARG): $(DEPS)
	$(CC) $(CFLAGS) -o $@ $(DEPS)

main.o: main.cpp 
	$(CC) $(CFLAGS) -c -o $@ $<

#General rule for all other files with header to generate
%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o *Q1
