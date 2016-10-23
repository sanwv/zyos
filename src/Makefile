AS=as -Iinclude
LD=ld
CC=gcc
CFLAGS=-m32 -Wall -pedantic -W -nostdlib -nostdinc -Wno-long-long -I include -fomit-frame-pointer

KERNEL_OBJS=load.o init.o scr.o

.s.o:
	${AS} $< -o $*.o

all: boot.bin
	dd bs=1M count=1 if=boot.bin of=../a.img conv=notrunc

boot.bin: bootsect kernel
	cat bootsect kernel > boot.bin

bootsect: bootsect.o
	${LD} --oformat binary -N -e start -Ttext 0x7c00 -o bootsect $<
load.o:
	${AS} --32 load.s -o load.o 

kernel: ${KERNEL_OBJS}
	${LD} -m elf_i386 --oformat binary -N -e pm_mode -Ttext 0x0000 -o $@ ${KERNEL_OBJS}

clean:
	rm -f *.o boot.bin bootsect kernel

dump:
	objdump -D -b binary -mi386 --adjust-vma 0x7c00 -Maddr16,data16 boot.bin

init.o: init.c scr.c include/scr.h
