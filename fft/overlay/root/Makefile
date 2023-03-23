CC = riscv64-unknown-linux-gnu-gcc
CFLAGS := -O3 -static -DRISCV

#CC = gcc
#CFLAGS := -O3 -std=gnu99

fft: fft.c
	        ${CC} ${CFLAGS} -o fft fft.c -lm

clean:
	        rm -f fft
