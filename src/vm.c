#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#include "../include/global.h"
#include "../include/ram.h"
#include "../include/vm.h"
#include "../include/instructions.h"

void sail_placeholder(vm_runtime* vm) {
	return;
}

void (*vm_instructionset[])(vm_runtime*) = {
	// ETC
	sail_instruction_SYSCALL,		
	sail_instruction_FLAG_RESET,
	
	// MOV
	sail_instruction_MOV_VALUETOREG, 
	sail_instruction_MOV_REGTOREG, 	

	// MATH
	sail_instruction_ADD_VALTOREG,
	sail_instruction_ADD_REGTOREG,		
	sail_instruction_MUL_REG,
	sail_instruction_DIV_REG,		
	sail_instruction_INC_REG,
	sail_instruction_DEINC_REG,

	// GOTO
	sail_instruction_GTO_IFEQUAL,	
	sail_instruction_GTO,		
	sail_instruction_GTO_IFNEQUAL,		
	sail_instruction_GTO_IFLESS, 		
	sail_instruction_GTO_IFMORE,		

	sail_instruction_COMP_REGTOREG,		
	sail_placeholder,		
	sail_placeholder,			
	sail_placeholder,			
	sail_placeholder,			
	sail_placeholder,			
	sail_placeholder,		
	sail_instruction_PUSH_REG,		
	sail_instruction_PUSH_VALUE,			
	sail_instruction_POP_REG,			
	sail_instruction_DUPE,			
};

vm_runtime init_vm(uint8_t* bytecode) {
	vm_runtime res; 
	res.pc = 0;
	res.bytecode = bytecode;
	res.ram = vm_init_memory();
	res.stack = vm_init_stack();
	res.registers = calloc(4, sizeof(uint32_t*)); 
	res.instruction = res.bytecode[res.pc];
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
	// read the header
	int i = 0;
	vm->hsize = 4;
	uint8_t byte = vm->bytecode[vm->pc];
	while (true) {
		if (byte == 0x7F && vm->bytecode[i+1] == 0xFF && vm->bytecode[i+2] == 0xFF && vm->bytecode[i+3] == 0xFF) {
			break;
		}
		vm->hsize++;
		vm_ram_write(&vm->ram, i, byte);
		byte = vm->bytecode[++i];
	}

	// offset bytecode to compensate for pc offset caused by the header
	vm->bytecode += vm->hsize;
	vm->instruction = vm->bytecode[vm->pc];

	// start interpreting the bytecode
	while (true) {
		log("running %02x, (pc = %i)\n", vm->instruction, vm->pc);
		vm_instructionset[vm->instruction](vm);
		
		vm->instruction = vm->bytecode[++vm->pc];
#ifdef DELAY
		sleep(DELAY);
#endif
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
		exit(1);
	}

	FILE* source = fopen(argv[argc - 1], "rb");
	fseek(source, 0, SEEK_END);
	unsigned long program_size = ftell(source);
	rewind(source);
	
	uint8_t* bytecode = malloc(program_size);
	
	if (!fread(bytecode, 1, program_size, source)) {
#ifdef INTERACTIVE
		printf(RED "Error: unable to read file\n" RESET);
#endif
		exit(1);
	}

	
#ifdef DEBUG
	log("%s", "running with bytes: ");
	for (int i = 0; i < program_size; i++) {
		printf("%02x ", bytecode[i]);
	}
	log("\n");
#endif

	vm_runtime sail_vm = init_vm(bytecode);
	fclose(source);
	vm_run(&sail_vm);
}
