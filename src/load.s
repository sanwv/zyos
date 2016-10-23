    .text
    .code32
    .global pm_mode
    .include "kernel.inc"
    .org 0

pm_mode:
    #设置段
   movl $DATA_SEL, %eax
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

   call init
   jmp .
