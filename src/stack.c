#include <stdint.h>
#include <stdlib.h>

#include "stack.h"

vm_stack* vm_stack_init() {
	vm_stack* stack = malloc(sizeof(vm_stack*));
	return stack;
}

uint32_t* vm_stack_peek(vm_stack *stack) {
	return &stack->stack[stack->stack_size];
}

void vm_stack_push(vm_stack *stack, uint8_t value) {
	stack->stack_size++;
	stack->stack = realloc(stack->stack, stack->stack_size);
	stack->stack[stack->stack_size] = value;
}

uint32_t vm_stack_pop(vm_stack *stack) {
	uint8_t popped_value = stack->stack[stack->stack_size];
	stack->stack_size--;
	stack->stack = realloc(stack->stack, stack->stack_size);
	return popped_value;
}
