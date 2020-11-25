CC:=g++
CFLAGS:=-g -std=c++11
LDFLAGS=-lX11 

%.o: %.cpp
	$(CC) $^ -c $(CFLAGS)

screengrab: screengrab.o
	$(CC) -o $@ $^ $(LDFLAGS)
	./$@

watch:
	echo *.cpp | entr make

clean:
	rm -rfv *.o screengrab

.PHONY: clean watch

