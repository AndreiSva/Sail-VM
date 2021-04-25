#include <stdio.h>

#include "../include/syscall.h"
#include "../include/vm.h"
#include "../include/global.h"

void call_clear(vm_runtime* vm) {
#ifdef __WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif
	clrscr();
}

void call_exit(vm_runtime* vm) {
	log("PROGRAM EXIT WITH CODE %i\n", vm->registers[1]);
	exit(vm->registers[1]);
}

void call_out(vm_runtime* vm) {
	for (int i = vm->registers[1]; i < vm->registers[2]; i++) {
		putchar(vm_ram_read(&vm->ram, i));
	}
}

void call_in(vm_runtime* vm) {
	char buffer[vm->registers[2]];
	fgets(buffer, vm->registers[2], stdin);
	
	for (int i = 0; i < vm->registers[2]; i++) {
		vm_ram_write(&vm->ram, i + vm->registers[1], buffer[i]);
	}
}

void (*vm_syscalls[])(vm_runtime*) = {
	call_exit,
	call_out,
	call_in,
	call_clear,
};

void vm_syscall(vm_runtime* vm, char call) {
	vm_syscalls[call](vm);
}
