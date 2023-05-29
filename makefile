CC=gcc
CFLAGS=-Wall -std=c17 -pedantic -I include/
OBJ=build/errors.o build/genetic.o build/graphic.o build/init.o build/io.o build/parser.o build/tools.o build/main.o
LDLIBS=-lMLV -lm
EXEC=travelling_salesman

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDLIBS)

build/errors.o: src/errors.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c -o $@ $<

build/genetic.o: src/genetic.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/graphic.o: src/graphic.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/init.o: src/init.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/io.o: src/io.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/parser.o: src/parser.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/tools.o: src/tools.c
	$(CC) $(CFLAGS) -c -o $@ $<

build/main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f build/*.o

mrproper: clean
	rm -f $(EXEC)
