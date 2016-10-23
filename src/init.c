#include <scr.h>
#include <kernel.h>

unsigned long long *idt = ((unsigned long long *)IDT_ADDR);
unsigned long long *gdt = ((unsigned long long *)GDT_ADDR);
static void isr_entry(int index, unsigned long long offset){
    //TODO
}
static void idt_install(void){
    unsigned int i = 0;
    struct DESCR {
        unsigned short length;
        unsigned long address;
    } __attribute__((packed)) idt_descr = {256*8-1, IDT_ADDR};
    for(i=0; i<VALID_ISR; i++){
        isr_entry(i, (unsigned int)(isr[(i<<1)+1]));
    }
    for(i++;i<256;i++){
        isr_entry(i,(unsigned int)default_isr);
    }
    __asm__("lidt %0\n\t"::"m"(idt_descr));
}

void init(void) {
    set_cursor(0,0);
    print_c('A', YELLOW, BLACK );
    print_c('B', YELLOW, BLACK );
    print_c('C', YELLOW, BLACK );
}
