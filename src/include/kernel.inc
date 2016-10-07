.set IDT_ADDR, 0x80000
.set IDT_SIZE, (256*8)

.set GDT_ENTRIES, 5
.set GDT_SIZE, (8*GDT_ENTRIES)
.set GDT_ADDR, (IDT_ADDR+IDT_SIZE) #gdt after idt

.set CODE_SEL, 0x08
.set DATA_SEL, 0x10


.set KERNEL_SECT, 72

.set STACK_BOT, 0xa0000 #内核栈顶640k
