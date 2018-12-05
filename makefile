#makefile for p6
#
CFLAGS = -g -Wall -std=c99

objects = oss user
all: $(objects)

$(objects): %: %.c
	$(CC) $(CLFAGS) -o $@ $< -pthread

clean:
	rm $(objects) *.txt
