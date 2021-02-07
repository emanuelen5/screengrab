CC:=g++
CFLAGS:=-g -std=c++11
LDFLAGS=-lX11 -lpthread

all: draw screengrab

%.o: %.cpp
	$(CC) $^ -c $(CFLAGS)

draw: draw.o
	$(CC) -o $@ $^ $(LDFLAGS)
	./$@

screengrab: screengrab.o
	$(CC) -o $@ $^ $(LDFLAGS)
	./$@

watch:
	echo *.cpp | entr make

clean:
	rm -rfv *.o screengrab draw

.PHONY: clean watch

