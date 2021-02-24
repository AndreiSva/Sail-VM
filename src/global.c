#include "global.h"

#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>

uint8_t parse_int(uint8_t* x) {
	uint8_t y[4] = {x[0], x[1], x[2], x[3]};
	free(x);
	return y[0] | (y[1] << 8) | (y[2] << 16) | (y[3] << 24);
}

#ifdef DEBUG
void print_reg(vm_runtime* vm) {
	printf("{ %" PRIu32 " %" PRIu32 " %" PRIu32 " %" PRIu32 " }\n", vm->registers[0], vm->registers[1], vm->registers[2], vm->registers[3]);
}
#endif

