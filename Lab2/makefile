all: dodawanieLong

dodawanieLong: dodawanieLong.o
	ld -m elf_i386 -o dodawanieLong dodawanieLong.o

dodawanieLong.o: dodawanieLong.s
	as --32 --gstabs -o dodawanieLong.o dodawanieLong.s
