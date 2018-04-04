all: dodawanieLong odejmowanieLong

dodawanieLong: dodawanieLong.o
	ld -m elf_i386 -o dodawanieLong dodawanieLong.o

dodawanieLong.o: dodawanieLong.s
	as --32 --gstabs -o dodawanieLong.o dodawanieLong.s

odejmowanieLong: odejmowanieLong.o
	ld -m elf_i386 -o odejmowanieLong odejmowanieLong.o

odejmowanieLong.o: odejmowanieLong.s
	as --32 --gstabs -o odejmowanieLong.o odejmowanieLong.s

