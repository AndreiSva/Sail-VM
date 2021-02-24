#include "instructions.h"
#include "global.h"
#include <inttypes.h>
#include <stdint.h>
#include "vm.h"

void sail_instruction_EXT(vm_runtime *vm) {
#ifdef DEBUG
	puts("PROGRAM EXIT");
#endif
	exit(0);	
}

void sail_instruction_SYSCALL(vm_runtime *vm) {
	return;
}

void sail_instruction_GTO(vm_runtime *vm) {
	vm->pc = parse_int(vm_read32(vm)) - 1;
#ifdef DEBUG
	printf("jumping to %i (%02x)\n", vm->pc + 1, vm->bytecode[vm->pc + 1]);
#endif
	vm->instruction = &vm->bytecode[vm->pc];

}


/* MOVE */

void sail_instruction_MOVREGTOREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[vm->pc + 2]] = vm->registers[vm->bytecode[vm->pc + 1]];
#ifdef DEBUG
	printf("moved reg %i into reg %i\n", vm->bytecode[vm->pc + 1], vm->bytecode[vm->pc + 2]);
	print_reg(vm);
#endif
	vm->pc += 2;
	
}

void sail_instruction_MOVVALUETOREG(vm_runtime *vm) {
	unsigned int target = (unsigned int) vm->bytecode[vm->pc + 1];
				
	vm->pc++;
	vm->registers[target] = parse_int(vm_read32(vm));
#ifdef DEBUG
	printf("moved %" PRIu32 " into reg %i\n", vm->registers[target], target);
	print_reg(vm);
#endif
}

/* MATH */

void sail_instruction_ADDVALTOREG(vm_runtime *vm) {
	unsigned int target = (unsigned int) vm->bytecode[++vm->pc];
	unsigned int value = parse_int(vm_read32(vm));

	vm->registers[target] += value;

#ifdef DEBUG
	printf("adding %" PRIu32 " into reg %i\n", value, target);
	print_reg(vm);
#endif
}

void sail_instruction_ADDREGTOREG(vm_runtime *vm) {
	unsigned int target1 = (unsigned int) vm->bytecode[++vm->pc];
	unsigned int target2 = (unsigned int) vm->bytecode[++vm->pc];
	
	vm->registers[target1] += vm->registers[target2];

#ifdef DEBUG
	printf("adding reg %i into reg %i\n", target2, target1);
	print_reg(vm);
#endif
}
