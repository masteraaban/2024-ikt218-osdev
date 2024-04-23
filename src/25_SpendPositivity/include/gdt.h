#ifndef GDT_H
#define GDT_H

// Integer type definitions
typedef unsigned int   u32int;
typedef unsigned short u16int;
typedef unsigned char  u8int;
typedef int            s32int;
typedef short          s16int;
typedef char           s8int;

// GDT (Global Descriptor Table) entry structure
struct gdt_entry_struct
{
   u16int limit_low;          
   u16int base_low;           
   u8int  base_middle;        
   u8int  access;             
   u8int  granularity;
   u8int  base_high;          
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

// GDT pointer structure
struct gdt_ptr_struct
{
   u16int limit;              
   u32int base;               
} __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// Initialize descriptor tables (GDT)
void init_descriptor_tables();

#endif // GDT_H
