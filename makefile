#explanation on this folder's readme.md
source=./src/main.c ./lib/ascii_grid.c ./lib/lib_ppm.c ./lib/char_queue.c ./lib/char_double_queue.c ./lib/folder_string.c

ifeq ($(OS), Windows_NT)
    EXECPATH := bin\\windows\\
else
    EXECPATH := bin/linux/
	LIBSOPATH := LD_LIBRARY_PATH=$(EXECPATH)
endif


includes=-Iinclude
libs=-L$(EXECPATH) -lrust_lib -lncurses
output=$(EXECPATH)main.exe
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default : $(source)
	$(compiler) $(flags) $(warn) $(includes) $(source) $(libs) -o $(output)

build_ignore: $(source)
	$(compiler) $(flags) $(includes) $(source) $(libs) -o $(output)


run: $(output)
	$(LIBSOPATH) ./$(output) $(image) $(invert)
