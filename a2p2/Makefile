all: genkey

%.o: %.c
	gcc -c -std=c99 -Wall $< -o $@

genkey: genkey.o a.o g.o s.o
	gcc -std=c99 -Wall $^ -o $@

