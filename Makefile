CC=clang
CFLAGS=-I. -g -rdynamic
DEPS = 
OBJ = main.o crash_function.o crash_handler.o


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

crasher.exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)