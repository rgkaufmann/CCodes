OBJECTS=Complete.o
DEVICE=msp430g2553
INSTALL_DIR=C:\ti\msp430-gcc

GCC_DIR = $(INSTALL_DIR)\bin
SUPPORT_FILE_DIRECTORY = $(INSTALL_DIR)\include

CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -Os
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY) -T $(DEVICE).ld

elf: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -g -o Complete.elf
asm:
	$(CC) $(CFLAGS) $(LFLAGS) $? -S Complete.c

clean:
	rm *.o *.elf *.s


debug: all
	$(GDB) Complete.elf
