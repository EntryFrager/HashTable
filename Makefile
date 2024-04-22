CC = g++

CFLAGS = -c -O3 -msse4.2 -mavx -mavx2 -masm=intel -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline		\
	-Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default		    									\
	-Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy            								\
	-Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers 								\
	-Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing   								\
	-Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

INCLUDES = include/hash_table.h include/hash_func.h include/hash_table_statistics.h include/input.h include/test.h include/my_strcmp.h list/list.h error/error.h utilities/utils.h

SOURCES = main.cpp hash_table.cpp hash_func.cpp hash_table_statistics.cpp input.cpp test.cpp my_strcmp.cpp list/list.cpp utilities/utils.cpp error/error.cpp

OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = hash_table.exe

VPATH = ./src/

all: asm_hash asm_strcmp $(SOURCES) $(INCLUDES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CC) $(OBJECTS) hash_func_asm.o my_strcmp_asm.o -o $@

asm_hash:  ./src/hash_func.asm
	@nasm -f elf64 ./src/hash_func.asm -o hash_func_asm.o

asm_strcmp: ./src/my_strcmp.asm
	@nasm -f elf64 ./src/my_strcmp.asm -o my_strcmp_asm.o

.cpp.o: $(INCLUDES) $(SOURCES)
	@$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
		clean_debug

clean:
	rm -rf *.o hash_table
	rm -rf ./list/*.o
	rm -rf ./error/*.o
	rm -rf ./utilities/*.o
	rm -rf hash_table.exe

clean_debug:
	rm -rf ./debug/

clean_plot:
	rm -rf ./plot/
