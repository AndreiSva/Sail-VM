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

void sail_instruction_GTO(vm_runtime *vm) {
	vm->pc = parse_int(vm_read32(vm));
	vm->instruction = &vm->bytecode[vm->pc];
#ifdef DEBUG
	printf("jumping to %i (%02x)\n", vm->pc, vm->bytecode[vm->pc]);
#endif

}

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
