#explanation on this folder's readme.md
source=./src/main.c ./lib/ascii_grid.c ./lib/lib_ppm.c ./lib/char_queue.c ./lib/char_double_queue.c ./lib/folder_string.c

ifeq ($(OS), Windows_NT)
    EXECPATH := ./bin/windows
	output=$(EXECPATH)/ascii_grid.exe
	RUSTLIB=-lrust_lib.dll
	RUNCOMMAND=$(EXECPATH)/$(output)
else
    EXECPATH := bin/linux/
	output=$(EXECPATH)ascii_grid
	RUNCOMMAND=LD_LIBRARY_PATH=$(EXECPATH) ./$(output)
	RUSTLIB=-lrust_lib
endif


includes=-Iinclude
libs=-L$(EXECPATH) $(RUSTLIB)
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default : $(source)
	$(compiler) $(flags) $(warn) $(includes) $(source) $(libs) -o $(output)

build_ignore: $(source)
	$(compiler) $(flags) $(includes) $(source) $(libs) -o $(output)

run: $(output)
	$(RUNCOMMAND) $(image) $(invert)
