#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "global.h"
#include "vm.h"
#include "ram.h"

vm_runtime* init_vm(uint8_t* bytecode) {
	vm_runtime* res = (vm_runtime*) calloc(sizeof(vm_runtime*), 1);
	res->bytecode = bytecode;
	res->sail_ram = vm_init_memory();
	res->registers = calloc(sizeof(uint32_t), 4);
	return res;
}

uint8_t* vm_read32(vm_runtime *vm) {
	uint8_t* res = calloc(sizeof(uint8_t), 4);
	for (int i = 0; i < 4; i++) {
		res[i] = *(&vm->bytecode[vm->pc + i + 1]);
	}
	vm->pc += 4;
	return res;
}

void vm_run(vm_runtime* vm) {
	uint8_t* instruction = &vm->bytecode[vm->pc];
	while (true) {
#ifdef DEBUG
		printf("running %02x, (pc = %i)\n", *instruction, vm->pc);
#endif
		switch (*instruction) {
			case (OP_EXT):
#ifdef DEBUG
				puts("PROGRAM EXIT");
#endif
				exit(0);
				break;
			case (OP_MOV_VALTOREG):
				;
				unsigned int target = (unsigned int) vm->bytecode[vm->pc + 1];
				
				vm->pc++;
				vm->registers[target] = parse_int(vm_read32(vm));
#ifdef DEBUG
				printf("moved %" PRIu32 " into reg %i\n", vm->registers[target], target);
				print_reg(vm);
#endif
				break;
			case (OP_MOV_REGTOREG):
				vm->registers[vm->bytecode[vm->pc + 2]] = vm->registers[vm->bytecode[vm->pc + 1]];
#ifdef DEBUG
				printf("moved reg %i into reg %i\n", vm->bytecode[vm->pc + 1], vm->bytecode[vm->pc + 2]);
				print_reg(vm);
#endif
				vm->pc += 2;
				break;
			case (OP_GTO):
				vm->pc = parse_int(vm_read32(vm));
				instruction = &vm->bytecode[vm->pc];
#ifdef DEBUG
				printf("jumping to %i (%02x)\n", vm->pc, vm->bytecode[vm->pc]);
#endif
				continue;
			default:
#ifdef DEBUG
				printf("%" PRIu32 "\n", OP_GTO);
				puts("PROGRAM ERROR");
#endif
				exit(1);
		}
		instruction = &vm->bytecode[++vm->pc];
	}
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		printf(RED "Error: Please specify a source file\n" RESET);	
		return 1;
	}

	if (access(argv[argc - 1], F_OK) != 0) {
		printf(RED "Error: file %s not found\n" RESET, argv[argc - 1]);
		return 1;
	}

	FILE* source = fopen(argv[argc - 1], "rb");
	fseek(source, 0, SEEK_END);
	unsigned long program_size = ftell(source);
	rewind(source);
	
	uint8_t* bytecode = malloc(program_size);
	fread(bytecode, 1, program_size, source);
	
#ifdef DEBUG
	printf("%s", "running with bytes: ");
	for (int i = 0; i < program_size; i++) {
		printf("%02x ", bytecode[i]);
	}
	printf("\n");
#endif

	vm_runtime* sail_vm = init_vm(bytecode);
	vm_run(sail_vm);
}
