CC=gcc
CFLAGS=
LDFLAGS=
EXEC=sokoban

all: $(EXEC)

$(EXEC): main.o sdlsoko.o sokoban.o 
	$(CC) -o $@ $^ $(LDFLAGS) -lSDL

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) -lSDL

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)