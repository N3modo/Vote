OBJS	= Main.o Condorcet.o Uninominal.o utilitaires.o
SOURCE	= Main.c Condorcet.c Uninominal.c utilitaires.c
HEADER	= Main.h Condorcet.h Uninominal.h utilitaires.h
OUT	= project_vote.exe
CC	 = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lm -lgmp

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LDFLAGS)

Main.o: Main.c
	$(CC) $(CFLAGS) Main.c

Condorcet.o: Condorcet.c
	$(CC) $(CFLAGS) Condorcet.c

Uninominal.o: Uninominal.c
	$(CC) $(CFLAGS) Uninominal.c

utilitaires.o: utilitaires.c
	$(CC) $(CFLAGS) utilitaires.c


clean:
	rm -f $(OBJS) $(OUT) *~
