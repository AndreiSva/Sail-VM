#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

#include "global.h"
#include "ram.h"
#include "vm.h"

#include "instructions.h"

void sail_placeholder(vm_runtime* vm) {
	return;
}

void (*vm_instructionset[])(vm_runtime*) = {
	sail_instruction_EXT, 			/* 0x00 */
	sail_instruction_SYSCALL,		/* 0x01 */
	
	// MOV
	sail_instruction_MOV_VALUETOREG, 	/* 0x02 */
	sail_instruction_MOV_REGTOREG, 		/* 0x03 */

	//MATH
	sail_instruction_ADD_VALTOREG,		/* 0x04 */
	sail_instruction_ADD_REGTOREG,		/* 0x05 */
	sail_instruction_MUL_REG,		/* 0x06 */
	sail_instruction_DIV_REG,		/* 0x07 */

	sail_instruction_GTO,			/* 0x08 */
	sail_instruction_GTO,			/* 0x09 */
	sail_instruction_GTO_IFEQUAL,		/* 0xA  */
	sail_instruction_GTO_IFNEQUAL,		/* 0xB  */
	sail_instruction_GTO_IFLESS, 		/* 0xC  */
	sail_instruction_GTO_IFMORE,		/* 0xD  */
	sail_placeholder,			/* 0xE  */
	sail_placeholder,			/* 0xF  */
	sail_placeholder,			/* 0x10 */
	sail_placeholder,			/* 0x11 */
	sail_placeholder,			/* 0x12  */
	sail_placeholder,			/* 0x13  */
	sail_placeholder,			/* 0x14  */
	sail_placeholder,			/* 0x15  */
	sail_placeholder,			/* 0x16  */
	sail_placeholder,			/* 0x17  */
	sail_placeholder,			/* 0x18  */
	sail_placeholder,			/* 0x19  */
	sail_placeholder,			/* 0x1A  */
	sail_placeholder,			/* 0x1B  */
	sail_placeholder,			/* 0x1C  */
	sail_placeholder,			/* 0x1D  */
	sail_placeholder,			/* 0x1E  */
	sail_placeholder,			/* 0x1F  */
	sail_placeholder,			/* 0x20  */
	sail_placeholder,			/* 0x21  */
	sail_placeholder,			/* 0x22  */
	sail_placeholder,			/* 0x23  */
	sail_placeholder,			/* 0x24  */
	sail_placeholder,			/* 0x25  */
	sail_placeholder,			/* 0x26  */
	sail_placeholder,			/* 0x27  */
	sail_placeholder,			/* 0x28  */
	sail_placeholder,			/* 0x29  */
};

vm_runtime* init_vm(uint8_t* bytecode) {
	vm_runtime* res = (vm_runtime*) calloc(1, sizeof(vm_runtime));
	res->pc = 0;
	res->bytecode = bytecode;
	res->sail_ram = vm_init_memory();
	res->registers = (uint32_t*) calloc(4, sizeof(uint32_t)); 
	res->instruction = &res->bytecode[res->pc];
	return res;
}

uint8_t* vm_read32(vm_runtime* vm) {
	uint8_t* res = malloc(4 * sizeof(uint8_t));
	for (int i = 0; i < 4; i++) {
		res[i] = *(&vm->bytecode[vm->pc + i + 1]);
	}
	vm->pc += 4;
	return res;
}

void vm_run(vm_runtime* vm) {
	while (true) {
#ifdef DEBUG
		printf("running %02x, (pc = %i)\n", *vm->instruction, vm->pc);
#endif		
		vm_instructionset[*vm->instruction](vm);
		
		vm->instruction = &vm->bytecode[++vm->pc];
	}
}

int main(int argc, char** argv) {
	if (argc <= 1) {
#ifdef INTERACTIVE
		printf(RED "Error: Please specify a source file\n" RESET);
#endif
		return 1;
	}
#ifdef INTERACTIVE	
	if (argv[argc - 1][0] == '-') {
		switch (argv[argc - 1][1]) {
			case ('v'):
				printf(

BLUE "   _____       _ ___    ____  ___\n"
"  / ___/____ _(_) / |  / /  |/  /\n"
"  \\__ \\/ __ `/ / /| | / / /|_/ /\n"
" ___/ / /_/ / / / | |/ / /  / / \n"
"/____/\\__,_/_/_/  |___/_/  /_/  \n"
RESET
GREEN "*-----------------------------*\n" RESET
#ifndef DEBUG
GREEN "version: " RESET YELLOW VERSION "\n" RESET
#else
GREEN "version: " RESET YELLOW "DEBUG\n" RESET
#endif
GREEN "platform: " RESET YELLOW PLATFORM " (%s)\n" RESET

"\nfor more information visit https://github.com/AndreiSva/Sail-VM\n"
, ARCHITECTURE);
				exit(0);
		}
	}
#endif

	if (access(argv[argc - 1], F_OK) != 0) {
#ifdef INTERACTIVE
		printf(RED "Error: file %s not found\n" RESET, argv[argc - 1]);
#endif
		return 1;
	}

	FILE* source = fopen(argv[argc - 1], "rb");
	fseek(source, 0, SEEK_END);
	unsigned long program_size = ftell(source);
	rewind(source);
	
	uint8_t* bytecode = malloc(program_size);

	// causes a warning on some libc
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
