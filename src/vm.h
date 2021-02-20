#ifndef __vm
#define __vm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ram.h"

typedef enum {
	OP_EXT = 0x00, /* exit program */
	OP_GTO = 0x09, /* goto bytecode (GTO <location>) */
	OP_MOV_VALTOREG = 0x10, /* mov value to register (MOV <register>) */
	OP_MOV_REGTOREG = 0x11
} vm_opcodes;

typedef struct {
	uint8_t* bytecode;
	vm_memory* sail_ram;
	unsigned int pc;

	uint32_t* registers;
} vm_runtime;

vm_runtime* init_vm(uint8_t* bytecode);
void vm_run(vm_runtime* vm);

uint8_t* vm_read32(vm_runtime* vm);

#endif
