#explanation on this folder's readme.md
source=./src/main.c ./lib/lib_ppm.c
includes=-Iinclude
libs=-Lbin -lrust_lib.dll
output=./bin/main.exe
compiler=gcc
warn=-Wall -Wextra -Werror -pedantic
flags=-std=c99

default : $(source)
	$(compiler) $(flags) $(warn) $(includes) $(source) $(libs) -o $(output)

run: $(output)
	./$(output) $(image) $(invert)
