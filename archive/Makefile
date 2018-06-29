#
# BMSML Makefile
#

print-%: ; @echo $*=$($*)
CC=clang
CFLAGS=-Wall -O2
#CFLAGS+=-ansi -pedantic -std=c++11
INC=-I/usr/local/include
LIBS=-lreadline
#LIBS+=-L/usr/local/lib
OUTPUT=bmsml
#Strip Binary
STRIP=strip
#Binary Compressor
COMPRESSOR=upx

#Strip and compress binary flags.
STRIP_FLAGS=-s
COMPRESS_FLAGS=-9

grab: main.c
	$(CC) $< $(CFLAGS) $(LIBS)  -o $(OUTPUT)
run: main.c
	$(CC) $< $(LIBS)  -o $(OUTPUT)
	./$(OUTPUT)
compress:
	$(STRIP) $< $(STRIP_FLAGS) $(OUTPUT)
	$(COMPRESSOR) $< $(COMPRESS_FLAGS) $(OUTPUT)
