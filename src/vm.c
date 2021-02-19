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
	res->btecode = bytecode;
	res->sail_ram = vm_init_memory();
	res->registers = calloc(sizeof(uint32_t*), 1);
	return res;
}

void vm_run(vm_runtime *vm) {
	while (true) {
		uint8_t* instruction = &vm->btecode[vm->pc++];
#ifdef DEBUG
		printf("running %" PRIu8 "\n", *instruction);
#endif
		switch (*instruction) {
			case (OP_EXT):
#ifdef DEBUG
				puts("PROGRAM EXIT");
#endif
				exit(0);
				break;
			case (OP_MOV):
				;
				uint8_t value[4];
				unsigned int target = (unsigned int) vm->btecode[vm->pc + 1];
				for (int i = 0; i < 4; i++) {
					value[i] = *(&vm->btecode[vm->pc + i]);
				}
				vm->registers[target] = value[0] | (value[1] << 8) | (value[2] << 16) | (value[3] << 24); 
				vm->pc += 5;
#ifdef DEBUG
				printf("moved %" PRIu32 " into %i\n", vm->registers[target], target);
				printf("{ %" PRIu32 " %" PRIu32 " %" PRIu32 " %" PRIu32 " }\n", vm->registers[0], vm->registers[1], vm->registers[2], vm->registers[3]);
#endif
				break;
			default:
#ifdef DEBUG
				puts("PROGRAM ERROR");
#endif
				exit(1);
		}
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
