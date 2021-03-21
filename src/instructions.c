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

void goto_addr(vm_runtime* vm, uint32_t addr, char condition) {
	if (condition) {
		vm->pc = addr - 1;
		vm->instruction = &vm->bytecode[vm->pc];
#ifdef DEBUG
		printf("jumping to %i (%02x)\n", vm->pc + 1, vm->bytecode[vm->pc + 1]);
#endif
	}
}

void sail_instruction_EXT(vm_runtime *vm) {
#ifdef DEBUG
	printf("PROGRAM EXIT WITH EXIT CODE %i\n", vm->bytecode[vm->pc + 1]);
#endif
	exit(vm->bytecode[vm->pc + 1]);	
}

void sail_instruction_SYSCALL(vm_runtime *vm) {
	switch (vm->registers[0]) {
		case call_clear:
#ifdef __WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif
			clrscr();
			break;
	}
}


/* COMP */

void sail_instruction_COMP_REGTOREG(vm_runtime *vm) {
	uint32_t reg1 = vm->registers[vm->bytecode[++vm->pc]];
	uint32_t reg2 = vm->registers[vm->bytecode[++vm->pc]];

#ifdef DEBUG
	printf("comparing %i and %i\n", reg1, reg2);
#endif

	compare(vm, reg1, reg2);
}

/* GOTO */

void sail_instruction_GTO(vm_runtime *vm) {
	uint32_t value = parse_int(vm_read32(vm));
	vm->pc = value - 1;
	vm->instruction = &vm->bytecode[vm->pc];
}

void sail_instruction_GTO_IFEQUAL(vm_runtime *vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_equal));
}

void sail_instruction_GTO_IFLESS(vm_runtime *vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_lesserthan));
}

void sail_instruction_GTO_IFMORE(vm_runtime *vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_greaterthan));
}

void sail_instruction_GTO_IFNEQUAL(vm_runtime *vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_nequal));
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
	int reg_index = vm->bytecode[vm->pc];
	vm->registers[reg_index] = parse_int(vm_read32(vm));;
	
#ifdef DEBUG
	print_reg(vm);
#endif
}

/* MATH */

void sail_instruction_ADD_VALTOREG(vm_runtime *vm) {
	vm->pc++;
	int reg_index = vm->bytecode[vm->pc];
	vm->registers[reg_index] += parse_int(vm_read32(vm));;
	
#ifdef DEBUG
	print_reg(vm);
#endif

//	vm->pc++;
//	vm->registers[vm->bytecode[vm->pc]] += parse_int(vm_read32(vm));
//#ifdef DEBUG
//	print_reg(vm);
//#endif
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
