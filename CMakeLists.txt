cmake_minimum_required(VERSION 3.10)
project(sailvm)

file(GLOB build_files 
     "include/*.h"
     "src/*.c"
)

set(CMAKE_C_FLAGS_DEBUG "-g -D DEBUG=1 -D INTERACTIVE=1 -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "-02 -D INTERACTIVE=1")

option(interactive "disable interactive use" 1)

add_executable(sailvm ${build_files})
