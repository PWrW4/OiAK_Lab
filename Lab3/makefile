all: kalkulator

kalkulator: kalkulator.o
	ld -m elf_i386 -o kalkulator kalkulator.o

kalkulator.o: kalkulator.s
	as --32 --gstabs -o kalkulator.o kalkulator.s


