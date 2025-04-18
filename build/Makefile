#
#   Compiler/Linkder Flags
#
CC = gcc
CFLAGS += -O -A -D_TARGET -D_TARGET_BIG_ENDIAN

# Need to make sure that _NO_LOG is defined to not log all messages
CFLAGS  += -D _NO_LOG

# Need to enable embedded exports 
CFLAGS  += -D EMBEDDED_EXPORTS

LINK = gcc
EXEC = example.exe

OBJS = crc16fast.o memcpy.o serhost.o serstub.o userFunctions.o main.o

#
# ===== Targets =====
#
build: embedded


clean:
	rm -rf *.ihx *.s *.o *.lst *.rst *.map $(EXEC)

all: clean build

#
# ===== "C" Source Files =====
#
crc16fast.o : ../crc16fast.c
	$(CC) -c $(CFLAGS) ../crc16fast.c

memcpy.o : ../memcpy.c
	$(CC) -c $(CFLAGS) ../memcpy.c

serhost.o : ../serhost.c
	$(CC) -c $(CFLAGS) ../serhost.c

serstub.o : ../serstub.c
	$(CC) -c $(CFLAGS) ../serstub.c

userFunctions.o : ../userFunctions.c
	$(CC) -c $(CFLAGS) ../userFunctions.c
	
main.o : main.c
	$(CC) -c $(CFLAGS) main.c

embedded : $(OBJS)
	$(LINK) -o $(EXEC) $(LFLAGS) $(OBJS)
