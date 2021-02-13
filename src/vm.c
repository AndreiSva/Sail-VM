#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "global.h"
#include "vm.h"

vm_runtime* init_vm(FILE* source) {
	vm_runtime* res = (vm_runtime*) calloc(sizeof(vm_runtime*), 1);
	return res;
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		printf(RED "Error, Please specify a source file\n" RESET);	
		return 1;
	}

	if (access(argv[argc - 1], F_OK) != 0) {
		printf(RED "Error, file %s not found\n" RESET, argv[argc - 1]);
		return 1;
	}

	FILE* source = fopen(argv[argc - 1], "rb");
	init_vm(source);
}
