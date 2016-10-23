#ifndef KERNEL_H
#define KERNEL_H 


#define IDT_ADDR    0x80000
#define IDT_SIZE    (256*8)
#define GDT_ADDR    ((IDT_ADDR)+IDT_SIZE)
#define GDT_ENTRIES 5
#define GET_SIZE    (8*GDT_ENTRIES)


#endif
