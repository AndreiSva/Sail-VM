#ifndef __vm
#define __vm

#include <stdio.h>
#include <stdlib.h>

#include "ram.h"

typedef struct {
	FILE* source;
	unsigned int pc;
} vm_runtime;

vm_runtime* init_vm(FILE* source);
void vm_run(vm_runtime* vm);

#endif
