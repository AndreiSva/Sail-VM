#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "../include/stack.h"
#include "../include/vm.h"
#include "../include/instructions.h"
#include "../include/global.h"
#include "../include/flags.h"
#include "../include/syscalls.h"

void compare(vm_runtime* vm, uint32_t a, uint32_t b) {
	vm_set_flag(&vm->flags, flag_equal, a == b);
	vm_set_flag(&vm->flags, flag_nequal, a != b);
	vm_set_flag(&vm->flags, flag_greaterthan, a > b);
	vm_set_flag(&vm->flags, flag_lesserthan, a < b);
}

void goto_addr(vm_runtime* vm, uint32_t addr, char condition) {
	if (condition) {
		vm->pc = addr - 1;
		log("jumping to %i (%02x)\n", vm->pc + 1, vm->bytecode[vm->pc + 1]);
	} else {
		vm->pc += 4;	
	}
}

void sail_instruction_EXT(vm_runtime* vm) {
	log("PROGRAM EXIT WITH EXIT CODE %i\n", vm->bytecode[vm->pc + 1]);
	exit(vm->bytecode[vm->pc + 1]);	
}

void sail_instruction_SYSCALL(vm_runtime* vm) {
	vm_syscall(vm, vm->registers[0]);
}

void sail_instruction_FLAG_RESET(vm_runtime* vm) {
	vm_set_flag(&vm->flags, flag_equal, 0);
	vm_set_flag(&vm->flags, flag_greaterthan, 0);
	vm_set_flag(&vm->flags, flag_lesserthan, 0);
	vm_set_flag(&vm->flags, flag_nequal, 0);
	vm_set_flag(&vm->flags, flag_overflow, 0);
}

/* COMP */

void sail_instruction_COMP_REGTOREG(vm_runtime* vm) {
	uint32_t reg1 = vm->registers[vm->bytecode[++vm->pc]];
	uint32_t reg2 = vm->registers[vm->bytecode[++vm->pc]];

	log("comparing %u and %u\n", reg1, reg2);

	compare(vm, reg1, reg2);
}

/* GOTO */

void sail_instruction_GTO(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	vm->pc = value - 1;
}

void sail_instruction_GTO_IFEQUAL(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_equal));
}

void sail_instruction_GTO_IFLESS(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_lesserthan));
}

void sail_instruction_GTO_IFMORE(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_greaterthan));
}

void sail_instruction_GTO_IFNEQUAL(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	goto_addr(vm, value, vm_get_flag(&vm->flags, flag_nequal));
}


/* MOV */

void sail_instruction_MOV_REGTOREG(vm_runtime* vm) {
	vm->registers[vm->bytecode[vm->pc + 2]] = vm->registers[vm->bytecode[vm->pc + 1]];
	log("moved reg %i into reg %i\n", vm->bytecode[vm->pc + 1], vm->bytecode[vm->pc + 2]);
	print_reg(vm->registers);
	vm->pc += 2;
}

void sail_instruction_MOV_VALUETOREG(vm_runtime* vm) {
	vm->pc++;
	uint8_t reg_index = vm->bytecode[vm->pc];
	vm->registers[reg_index] = parse_int(vm_read32(vm));;
	
	print_reg(vm->registers);
}


/* STACK */

void sail_instruction_PUSH_REG(vm_runtime* vm) {
	vm_stack_push(&vm->stack, vm->registers[vm->bytecode[vm->pc + 1]]);
	vm->pc++;
}

void sail_instruction_PUSH_VALUE(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	vm_stack_push(&vm->stack, value);
	print_stack(&vm->stack);
	log("pushing value %d to stack\n", value);
}

void sail_instruction_POP_REG(vm_runtime* vm) {
	vm->registers[vm->bytecode[vm->pc + 1]] = vm_stack_pop(&vm->stack);
	print_stack(&vm->stack);
	print_reg(vm->registers);
	vm->pc++;
}

void sail_instruction_DUPE(vm_runtime* vm) {
	print_stack(&vm->stack);
	vm_stack_push(&vm->stack, *vm_stack_peek(&vm->stack));
}

/* MATH */

void sail_instruction_ADD_VALTOREG(vm_runtime* vm) {
	uint32_t value = parse_int(vm_read32(vm));
	
	if (vm->registers[vm->bytecode[vm->pc + 1]] > UINT32_MAX - value) {
		vm_set_flag(&vm->flags, flag_overflow, 1);
	}

	vm->registers[vm->bytecode[vm->pc + 1]] += value;
	print_reg(vm->registers);
	vm->pc++;
}

void sail_instruction_ADD_STACK(vm_runtime* vm) {
	uint32_t stack1 = vm_stack_pop(&vm->stack);
	uint32_t stack2 = vm_stack_pop(&vm->stack);
	
	if (stack1 > UINT32_MAX - stack2) {
		vm_set_flag(&vm->flags, flag_overflow, 1);
	}

	vm_stack_push(&vm->stack, stack1 + stack2);
}

void sail_instruction_ADD_REGTOREG(vm_runtime* vm) {
	vm->pc++;
	
	uint32_t reg1 = vm->registers[vm->bytecode[vm->pc]];
	uint32_t reg2 = vm->registers[vm->bytecode[vm->pc + 1]];
	
	if (reg1 > UINT32_MAX  - reg2) {
		vm_set_flag(&vm->flags, flag_overflow, 1);
	}

	vm->pc++;
	print_reg(vm->registers);
}

// TODO: add overflow checkers
void sail_instruction_SUB_VALTOREG(vm_runtime* vm) {
	vm->registers[vm->bytecode[++vm->pc]] -= parse_int(vm_read32(vm));
	print_reg(vm->registers);
}

void sail_instruction_SUB_STACK(vm_runtime* vm) {
	vm_stack_push(&vm->stack, vm_stack_pop(&vm->stack) - vm_stack_pop(&vm->stack));
}

void sail_instruction_SUB_REGTOREG(vm_runtime* vm) {
	vm->pc++;
	vm->registers[vm->bytecode[vm->pc]] -= vm->registers[vm->bytecode[vm->pc + 1]];

	print_reg(vm->registers);
}

void sail_instruction_INC_REG(vm_runtime* vm) {
	vm->registers[vm->bytecode[++vm->pc]]++;
	
	if (vm->registers[vm->bytecode[vm->pc]] == UINT32_MAX) {
		vm_set_flag(&vm->flags, flag_overflow, 1);
	}

	log("incrementing reg %i\n", vm->bytecode[vm->pc]);
	print_reg(vm->registers);
}

void sail_instruction_DEINC_REG(vm_runtime* vm) {
	vm->registers[vm->bytecode[++vm->pc]]--;
	
	if (vm->registers[vm->bytecode[vm->pc]] == 0) {
		vm_set_flag(&vm->flags, flag_overflow, 1);
	}

	log("deincrementing reg %i\n", vm->bytecode[vm->pc]);
	print_reg(vm->registers);
}

void sail_instruction_MUL_REG(vm_runtime* vm) {
	vm->registers[vm->bytecode[++vm->pc]] *= parse_int(vm_read32(vm));
	log("multiplying reg %i by \n", vm->bytecode[vm->pc]);
	print_reg(vm->registers);
}

void sail_instruction_DIV_REG(vm_runtime* vm) {
	vm->registers[vm->bytecode[++vm->pc]] /= parse_int(vm_read32(vm));
}
