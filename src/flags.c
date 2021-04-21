#include "../include/flags.h"
#include <stdint.h>

uint8_t vm_get_flag(vm_flags *flags, sail_flag_types index) {
	return flags->flags[index];
}

void vm_set_flag(vm_flags *flags, sail_flag_types type, uint8_t value) {
#ifdef DEBUG
#include <stdio.h>
printf("set flag %i to %i", type, value);
#endif
	flags->flags[type] = value;
}
