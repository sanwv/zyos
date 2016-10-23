#ifndef _ASM_H
#define _ASM_H

/*中断 */
#define cli() __asm__ ("cli\n\t")
#define sti() __asm__ ("sti\n\t")

/* 待速 */
#define halt() __asm__ ("cli;hlt\n\t");
#define idle() __asm__ ("jmp . \n\t");

/*io端口*/
#define inb(port) (__extension__({ \
            unsigned char __res; \
            __asm__ ("inb %%dx, %%al\n\t" \
                    :"=a"(__res) \
                    :"dx"(port)); \
            __res; \
            }))

#define outb(port,value) __asm__ ( \
        "outb %%al, %%dx\n\t"::"al"(value), "dx"(port))

#endif


