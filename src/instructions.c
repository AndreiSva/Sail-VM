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


/* MOV */

void sail_instruction_MOVREGTOREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[vm->pc + 2]] = vm->registers[vm->bytecode[vm->pc + 1]];
#ifdef DEBUG
	printf("moved reg %i into reg %i\n", vm->bytecode[vm->pc + 1], vm->bytecode[vm->pc + 2]);
	print_reg(vm);
#endif
	vm->pc += 2;
	
}

void sail_instruction_MOVVALUETOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] = parse_int(vm_read32(vm));
#ifdef DEBUG
	print_reg(vm);
#endif
}

/* MATH */

void sail_instruction_ADDVALTOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] += parse_int(vm_read32(vm));
#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_SUBVALTOREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]] -= parse_int(vm_read32(vm));
#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_ADDREGTOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] += vm->registers[vm->bytecode[vm->pc + 1]];
	vm->pc++;
#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_SUBREGTOREG(vm_runtime *vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] -= vm->registers[vm->bytecode[vm->pc + 1]];

#ifdef DEBUG
	print_reg(vm);
#endif
}

void sail_instruction_INCREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]]++;
#ifdef DEBUG
	printf("incrementing reg %i\n", vm->bytecode[vm->pc]);
	print_reg(vm);
#endif
}

void sail_instruction_DEINCREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]]--;
#ifdef DEBUG
	printf("deincrementing reg %i\n", vm->bytecode[vm->pc]);
	print_reg(vm);
#endif
}

void sail_instruction_MULREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]] *= parse_int(vm_read32(vm));
#ifdef DEBUG
	printf("multiplying reg %i by \n", vm->bytecode[vm->pc]);
	print_reg(vm);
#endif
}

void sail_instruction_DIVREG(vm_runtime *vm) {
	vm->registers[vm->bytecode[++vm->pc]] /= parse_int(vm_read32(vm));
}
