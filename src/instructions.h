#ifndef __instructions
#define __instructions

#include "vm.h"

void sail_instruction_EXT(vm_runtime* vm);
void sail_instruction_SYSCALL(vm_runtime* vm);

// COMP
void sail_instruction_COMP_REGTOREG(vm_runtime* vm);

// GOTO
void sail_instruction_GTO(vm_runtime* vm);
void sail_instruction_GTO_IFEQUAL(vm_runtime* vm);
void sail_instruction_GTO_IFNEQUAL(vm_runtime* vm);
void sail_instruction_GTO_IFLESS(vm_runtime* vm);
void sail_instruction_GTO_IFMORE(vm_runtime* vm);

// MOV
void sail_instruction_MOV_VALUETOREG(vm_runtime* vm);
void sail_instruction_MOV_REGTOREG(vm_runtime* vm);

// MATH
void sail_instruction_ADD_VALTOREG(vm_runtime* vm);
void sail_instruction_SUB_VALTOREG(vm_runtime* vm);
void sail_instruction_ADD_REGTOREG(vm_runtime* vm);
void sail_instruction_SUB_REGTOREG(vm_runtime* vm);
void sail_instruction_INC_REG(vm_runtime* vm);
void sail_instruction_DEINC_REG(vm_runtime* vm);
void sail_instruction_MUL_REG(vm_runtime* vm);
void sail_instruction_DIV_REG(vm_runtime* vm);
void sail_instruction_AND_REG(vm_runtime* vm);
void sail_instruction_OR_REG(vm_runtime* vm);
void sail_instruction_NOT_REG(vm_runtime* vm);
#endif
