#include <inttypes.h>
#include <stdint.h>

#include "vm.h"
#include "instructions.h"
#include "global.h"
#include "flags.h"

void compare(vm_runtime* vm, uint32_t a, uint32_t b) {
	vm_set_flag(&vm->flags, flag_equal, a == b);
	vm_set_flag(&vm->flags, flag_nequal, a != b);
	vm_set_flag(&vm->flags, flag_greaterthan, a > b);
	vm_set_flag(&vm->flags, flag_lesserthan, a < b);
}

void sail_instruction_EXT(vm_runtime *vm) {
#ifdef DEBUG
	printf("PROGRAM EXIT WITH EXIT CODE %i\n", vm->bytecode[vm->pc + 1]);
#endif
	exit(vm->bytecode[vm->pc + 1]);	
}

void sail_instruction_SYSCALL(vm_runtime *vm) {
	return;
}


/* COMP */

void sail_instruction_COMP_REGTOREG(vm_runtime *vm) {
	uint32_t reg1 = parse_int(vm_read32(vm));
	uint32_t reg2 = parse_int(vm_read32(vm));

	compare(vm, reg1, reg2);
}

/* GOTO */

void sail_instruction_GTO(vm_runtime *vm) {
		vm->pc = parse_int(vm_read32(vm)) - 1;
#ifdef DEBUG
		printf("jumping to %i (%02x)\n", vm->pc + 1, vm->bytecode[vm->pc + 1]);
#endif
		vm->instruction = &vm->bytecode[vm->pc];

}

void sail_instruction_GTO_IFEQUAL(vm_runtime *vm) {
	if (vm_get_flag(&vm->flags, flag_equal)) {
		vm->pc = parse_int(vm_read32(vm)) - 1;
		vm->instruction = &vm->bytecode[vm->pc];
	}
}

void sail_instruction_GTO_IFLESS(vm_runtime *vm) {
	return;
}

void sail_instruction_GTO_IFMORE(vm_runtime *vm) {
	return;
}

void sail_instruction_GTO_IFNEQUAL(vm_runtime *vm) {
	return;
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
