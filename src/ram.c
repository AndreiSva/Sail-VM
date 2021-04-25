#include "../include/ram.h"

vm_memory vm_init_memory() {
	vm_memory new_mem; 
	new_mem.capacity = 20;
	new_mem.mem = malloc(sizeof(uint32_t*) * 20);
	return new_mem;
}

void vm_ram_increase(vm_memory* target, unsigned long amount) {
	target->capacity += amount;
	target->mem = realloc(target->mem, target->capacity);
}

void vm_ram_write(vm_memory* target, uint32_t x, uint32_t y) {
	if (x >= target->capacity) {
		vm_ram_increase(target, x - target->capacity);
	}

	target->mem[x] = y;
}

uint32_t vm_ram_read(vm_memory* target, uint32_t x) {
	if (x > target->capacity) {
		vm_ram_increase(target, x - target->capacity);
	}

	return target->mem[x];
}


