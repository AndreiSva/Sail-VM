#include "flags.h"

bool vm_get_flag(vm_flags *flags, sail_flag_types type) {
		
}

void vm_set_flag(vm_flags *flags, sail_flag_types type, char value) {
	flags->value |= value;
}
