    .text
    .global pm_mode
    .include "kernel.inc"
    .org 0

pm_mode:
    #设置段
   movw $DATA_SEL, %ax
   movw %ax, %ds
   movw %ax, %es
   movw %ax, %fs
   movw %ax, %gs
   movw %ax, %ss
   movl $STACK_BOT, %esp

    #移动512字节后的代码到开始处
   cld
   movl $0x10200, %esi
   movl $0x200, %edi
   movl $(KERNEL_SECT-1)<<7, %ecx
   rep
   movsl
    #hello移动到视频内存
    movb $0x07, %al #色彩属性
    movl $msg, %esi
    movl $0xb8000, %edi
1:
    cmp $0, (%esi)
    je 1f
    movsb
    stosb
    jmp 1b
1:
    jmp .

msg:
    .string "Hello World!\x0"



