#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"
#include "../include/global.h"

vm_stack vm_init_stack() {
	vm_stack stack;
	stack.stack_size = 0;
	stack.stack = (uint32_t*) malloc(sizeof(uint32_t*));
	return stack;
}

uint32_t* vm_stack_peek(vm_stack *stack) {
	return &stack->stack[stack->stack_size - 1];
}

void vm_stack_push(vm_stack *stack, uint32_t value) {
	stack->stack_size++;
	stack->stack = (uint32_t*) realloc(stack->stack, stack->stack_size * sizeof(uint32_t*));
	stack->stack[stack->stack_size - 1] = value;
}

uint32_t vm_stack_pop(vm_stack *stack) {
	uint32_t popped_value = stack->stack[stack->stack_size - 1];
	stack->stack_size--;
	stack->stack = realloc(stack->stack, stack->stack_size * sizeof(uint32_t));
	return popped_value;
}

