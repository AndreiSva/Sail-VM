#ifndef __vm_flags
#define __vm_flags

#include <stdint.h>

#include "global.h"

typedef enum {
	flag_equal,
	flag_nequal,
	flag_greaterthan,
	flag_lesserthan,
} sail_flag_types;

typedef struct {
	uint8_t value;	
} vm_flags;

bool vm_get_flag(vm_flags* flags, sail_flag_types flag);
void vm_set_flag(vm_flags* flags, sail_flag_types type, bool value);

#endif
