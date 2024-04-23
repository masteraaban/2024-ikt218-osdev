#include "gdt.h"
#include "common.h" 

// External ASM function to load the new GDT
extern void gdt_flush(u32int);

// Internal function declarations
static void init_gdt();
static void gdt_set_gate(int num, u32int base, u32int limit, u8int access, u8int gran);

// GDT entries and pointer structure
gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

// Initialize the Global Descriptor Table (GDT) 
void init_descriptor_tables()
{
    init_gdt();  // Set up the GDT
}

// Setup GDT with predefined gates
static void init_gdt()
{
    // Set the GDT pointer and entries
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (u32int)&gdt_entries;

    // Configure the GDT entries
    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    gdt_flush((u32int)&gdt_ptr);  // Load the new GDT
}

// Define a GDT gate
static void gdt_set_gate(int num, u32int base, u32int limit, u8int access, u8int gran)
{
    // Set the base, limit, and access flags for the GDT entry
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt_entries[num].access      = access;
}