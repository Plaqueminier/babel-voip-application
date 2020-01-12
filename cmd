mkdir build && cd build &&  conan install .. && cmake .. -G "Unix Makefiles" && cmake –build .


cd .. && rm -rf build && mkdir build && cd build &&  conan install .. && cmake .. -G "Unix Makefiles" && cmake –build . && make && ./bin/babel

conan install .. -s "arch=x86"
