#ifndef __vm
#define __vm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ram.h"
#include "flags.h"

typedef struct {
	uint8_t* bytecode;
	uint8_t* instruction;
	vm_memory* sail_ram;
	unsigned int pc;
	vm_flags flags;
	uint32_t* registers;
} vm_runtime;

vm_runtime* init_vm(uint8_t* bytecode);
void vm_run(vm_runtime* vm);

// read the next 4 bytes into an array
uint8_t* vm_read32(vm_runtime* vm);

#endif
