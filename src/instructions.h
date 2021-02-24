#ifndef __instructions
#define __instructions

#include "vm.h"

void sail_instruction_EXT(vm_runtime* vm);
void sail_instruction_SYSCALL(vm_runtime* vm);
void sail_instruction_GTO(vm_runtime* vm);

// MOV
void sail_instruction_MOVVALUETOREG(vm_runtime* vm);
void sail_instruction_MOVREGTOREG(vm_runtime* vm);

// MATH
void sail_instruction_ADDVALTOREG(vm_runtime* vm);
void sail_instruction_SUBVALTOREG(vm_runtime* vm);
void sail_instruction_ADDREGTOREG(vm_runtime* vm);
void sail_instruction_SUBREGTOREG(vm_runtime* vm);
void sail_instruction_INCREG(vm_runtime* vm);
void sail_instruction_DEINCREG(vm_runtime* vm);
void sail_instruction_MULREG(vm_runtime* vm);
void sail_instruction_DIVREG(vm_runtime* vm);
#endif
