#include <stdint.h>
#include <stdio.h>

#include "../include/flags.h"
#include "../include/global.h"

uint8_t vm_get_flag(vm_flags *flags, sail_flag_types index) {
	return flags->flags[index];
}

void vm_set_flag(vm_flags *flags, sail_flag_types type, uint8_t value) {
	log("set flag %i to %i", type, value);
	flags->flags[type] = value;
}
