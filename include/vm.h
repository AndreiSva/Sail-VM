#ifndef __vm
#define __vm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ram.h"
#include "flags.h"
#include "stack.h"

typedef struct {
	uint8_t* bytecode;
	uint8_t instruction;

	vm_memory ram;
	vm_flags flags;
	vm_stack stack;

	uint32_t pc;
	size_t hsize;

	uint32_t* registers;
} vm_runtime;

vm_runtime init_vm(uint8_t* bytecode);
void vm_run(vm_runtime* vm);

// read the next 4 bytes into an array
uint8_t* vm_read32(vm_runtime* vm);

#endif
