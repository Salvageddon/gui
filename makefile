srctarget = src/source/gui/*.c
dlltarget = ./gui.dll
maintarget = src/source/main.c

all: build start

build:
	gcc -shared ${srctarget} -o ${dlltarget} -L. -llist -lhashlist -lSDL3 -lxmlReader

start:
	gcc ${maintarget} -o ./test -L. -llist -lhashlist -lSDL3 -lxmlReader -lgui
	./test