#include "../include/global.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

uint32_t parse_int(uint8_t* x) {
	uint8_t y[4] = {x[0], x[1], x[2], x[3]};
	free(x);
	return y[0] | (y[1] << 8) | (y[2] << 16) | (y[3] << 24);
}

#ifdef DEBUG
void print_reg(uint32_t* registers) {
	printf("{ %" PRIu32 " %" PRIu32 " %" PRIu32 " %" PRIu32 " }\n", registers[0], registers[1], registers[2], registers[3]);
}

void print_stack(vm_stack *stack) {
	printf("stack (%lu): { ", stack->stack_size);
	for (int i = 0; i < stack->stack_size; i++) {
		printf("%u ", stack->stack[i]);
	}
	printf("}\n");
}
#endif


