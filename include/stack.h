#ifndef __vm_stack
#define __vm_stack

#include <stdlib.h>
#include <stdint.h>

typedef struct {
	uint32_t* stack;
	unsigned long stack_size;
} vm_stack;

uint32_t* vm_stack_peek(vm_stack* stack);
void vm_stack_push(vm_stack* stack, uint32_t value);
uint32_t vm_stack_pop(vm_stack* stack);

vm_stack vm_init_stack();

#endif
