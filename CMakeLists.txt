cmake_minimum_required(VERSION 3.10)
project(sailvm)

file(GLOB build_files 
     "include/*.h"
     "src/*.c"
)

option(interactive "disable interactive use" 1)

set(version "dev")
set(CMAKE_C_FLAGS_DEBUG "-g -D INTERACTIVE=${interactive} -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "-O2 -D INTERACTIVE=${interactive} -D VERSION=\\\"${version}\\\"")

add_executable(sailvm ${build_files})

install(
	TARGETS sailvm
    PUBLIC_HEADER
    DESTINATION /usr/bin
)
