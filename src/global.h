#ifndef __global
#define __global

#include "vm.h"
#include <stdint.h>
#define bool char
#define true 1
#define false 0

#ifdef INTERACTIVE
#ifndef __WIN32
#define RED    "\x1B[31m"
#define BLUE   "\x1B[36m"
#define GREEN  "\x1B[32m"
#define YELLOW "\x1B[33m"
#define RESET  "\033[0m"
#else
#define RED    ""
#define BLUE   ""
#define GREEN  ""
#define YELLOW ""
#define RESET  ""
#endif

#if UINTPTR_MAX == 0xffffffff
#define ARCHITECTURE "32 bit"
#elif UINTPTR_MAX == 0xffffffffffffffff
#define ARCHITECTURE "64 bit"
#else
#define ARCHITECTURE "unknown"
#endif 

#ifdef __linux__
#define PLATFORM "Linux"
#elif __WIN32
#define PLATFORM "Win32"
#elif TARGET_OS_MAC
#define PLATFORM "MacOS"
#elif BSD
#define PLATFORM "BSD"
#else
#define PLATFORM "unknown"
#endif
#endif

#ifndef VERSION
#define DEBUG 1
#endif

uint32_t parse_int(uint8_t* x);

#ifdef DEBUG
void print_reg(vm_runtime* vm);
#endif



#endif
