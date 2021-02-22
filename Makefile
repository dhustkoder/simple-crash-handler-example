CC=clang
CFLAGS=-I. -O3 -DNDEBUG -rdynamic -g
DEPS = 
OBJ = main.o crash_function.o crash_handler.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

crasher.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o