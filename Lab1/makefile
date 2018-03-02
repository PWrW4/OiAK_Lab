all: hello writeText

hello: hello.o
	ld -o hello hello.o

hello.o: hello.s
	as -o hello.o hello.s

writeText: writeText.o
	ld -o writeText writeText.o

writeText.o: writeText.s
	as -o writeText.o writeText.s
