#include "global.h"

#include <stdint.h>
#include <unistd.h>
#include <inttypes.h>


uint8_t parse_int(uint8_t* x) { 
	return x[3] | (x[2] << 8) | (x[1] << 16) | (x[0] << 24);
}

#ifdef DEBUG
void print_reg(vm_runtime* vm) {
	printf("{ %" PRIu32 " %" PRIu32 " %" PRIu32 " %" PRIu32 " }\n", vm->registers[0], vm->registers[1], vm->registers[2], vm->registers[3]);
}
#endif
