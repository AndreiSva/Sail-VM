#ifndef __vm
#define __vm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ram.h"

typedef enum {
	OP_EXT = 0x00,
	OP_MOV = 0x10
} vm_opcodes;

typedef struct {
	uint8_t* btecode;
	vm_memory* sail_ram;
	unsigned int pc;

	uint32_t* registers;
} vm_runtime;

vm_runtime* init_vm(uint8_t* bytecode);
void vm_run(vm_runtime* vm);

#endif
