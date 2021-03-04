#include <inttypes.h>
#include <stdint.h>

#include "vm.h"
#include "instructions.h"
#include "global.h"

void compare(uint8_t a, uint8_t b) {
	
}

void sail_instruction_EXT(vm_runtime *vm) {
#ifdef DEBUG
	puts("PROGRAM EXIT");
#endif
	exit(0);	
}

void sail_instruction_SYSCALL(vm_runtime *vm) {
	return;
}

/* GOTO */

void sail_instruction_GTO(vm_runtime *vm) {
		vm->pc = parse_int(vm_read32(vm)) - 1;
#ifdef DEBUG
		printf("jumping to %i (%02x)\n", vm->pc + 1, vm->bytecode[vm->pc + 1]);
#endif
		vm->instruction = &vm->bytecode[vm->pc];

}

void sail_instruction_GTO_COMPREGTOREG(vm_runtime* vm) {

}

/* MOV */

void sail_instruction_MOV_REGTOREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[vm->pc + 2]] = vm->registers[vm->bytecode[vm->pc + 1]];
#ifdef DEBUG
	printf("moved reg %i into reg %i\n", vm->bytecode[vm->pc + 1], vm->bytecode[vm->pc + 2]);
	print_reg(vm);
#endif
	vm->pc += 2;
	
}

void sail_instruction_MOV_VALUETOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] = parse_int(vm_read32(vm));
#ifdef DEBUG
	print_reg(vm);
#endif
}

/* MATH */

void sail_instruction_ADD_VALTOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] += parse_int(vm_read32(vm));
#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_SUB_VALTOREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]] -= parse_int(vm_read32(vm));
#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_ADD_REGTOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] += vm->registers[vm->bytecode[vm->pc + 1]];
	vm->pc++;
#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_SUB_REGTOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] -= vm->registers[vm->bytecode[vm->pc + 1]];

#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_INC_REG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]]++;
#ifdef DEBUG
	printf("incrementing reg %i\n", vm->bytecode[vm->pc]);
	print_reg(vm);
#endif
}

void sail_instruction_DEINC_REG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]]--;
#ifdef DEBUG
	printf("deincrementing reg %i\n", vm->bytecode[vm->pc]);
	print_reg(vm);
#endif
}

void sail_instruction_MUL_REG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]] *= parse_int(vm_read32(vm));
#ifdef DEBUG
	printf("multiplying reg %i by \n", vm->bytecode[vm->pc]);
	print_reg(vm);
#endif
}

void sail_instruction_DIV_REG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]] /= parse_int(vm_read32(vm));
}
