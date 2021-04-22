#include <stdio.h>

#include "../include/syscall.h"
#include "../include/vm.h"

void call_clear(vm_runtime* vm) {
#ifdef __WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif
	clrscr();
}

void call_out(vm_runtime* vm) {

}

void (*vm_syscalls[])(vm_runtime*) = {
	call_clear,
	call_out,
};

void vm_syscall(vm_runtime* vm, char call) {
	vm_syscalls[call](vm);
}
