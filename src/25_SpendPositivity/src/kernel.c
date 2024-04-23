#include "libc/stdint.h"
#include "libc/stddef.h"
#include "libc/stdbool.h"
#include  "libc/stdarg.h"
#include <libc/stdio.h>
#include <multiboot2.h>
#include <gdt.h>
#include <common.h>
#include <monitor.h>

struct multiboot_info {
    uint32_t size;
    uint32_t reserved;
    struct multiboot_tag *first;
};

int kernel_main();

uint16_t lengthSq(uint16_t x, uint16_t y) {
    uint16_t r = x * x + y * y;
    return r;
}

int main(uint32_t magic, struct multiboot_info* mb_info_addr) {
    

    init_descriptor_tables(); // gdt
    monitor_clear(); // Clears the monitor screen.
    monitor_write("Hello world!"); // Writes to the monitor.

    return 0; 
}