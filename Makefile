##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##


all:
	mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake –build .
	make -C ./build

clean:
	rm -rf build

fclean: clean

re: fclean all

cclient:
	rm client

rec: cclient client
