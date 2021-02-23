#ifndef __instructions
#define __instructions

#include "vm.h"

void sail_instruction_EXT(vm_runtime* vm);
void sail_instruction_GTO(vm_runtime* vm);
void sail_instruction_MOVVALUETOREG(vm_runtime* vm);
void sail_instruction_MOVREGTOREG(vm_runtime* vm);

#endif
