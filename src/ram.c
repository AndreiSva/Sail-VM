#include <stdio.h>

#include "../include/ram.h"

vm_memory vm_init_memory() {
	vm_memory new_mem; 
	new_mem.capacity = 10;
	new_mem.mem = malloc(sizeof(uint32_t*) * new_mem.capacity);
	return new_mem;
}

void vm_ram_increase(vm_memory* target, uint32_t amount) {
	target->capacity += amount;
	target->mem = realloc(target->mem, sizeof(uint32_t) * target->capacity);
}

void vm_ram_write(vm_memory* target, size_t x, uint32_t y) {
	if (x >= target->capacity) {
		vm_ram_increase(target, 10);
	}
	target->mem[x] = y;
}

uint32_t vm_ram_read(vm_memory* target, size_t x) {
	if (x > target->capacity) {
		vm_ram_increase(target, x - target->capacity);
	}

	return target->mem[x];
}

