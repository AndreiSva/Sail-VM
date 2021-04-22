#ifndef __vm_syscalls
#define __vm_syscalls

#include "../include/vm.h"

void vm_syscall(vm_runtime* vm, char call);

void call_clear(vm_runtime* vm);
void call_out(vm_runtime* vm);

#endif
