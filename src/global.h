#ifndef __global
#define __global

#include <stdint.h>
#include "vm.h"
#define bool char
#define true 1
#define false 0

#define RED "\x1B[31m"
#define RESET "\033[0m"

uint8_t parse_int(uint8_t* x);

#ifdef DEBUG
void print_reg(vm_runtime* vm);
#endif

#endif
