#疑问gdt已经复制到idt之后了但lgdt还是载入的旧位置
    .text
    .global start
    .code16
    .include "kernel.inc"


start:
    #设置段信息
    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %ss
    movw $0x1000, %sp #栈顶位置
    #从软盘加载内核到0x1000处
    movw $0x1000, %ax
    movw %ax, %es
    xorw %bx, %bx #es:bs 目标位置
    #通过loop和函数来一个一个读取扇区si保存要读取的扇区号,bx保存读取到的位置
    movw $1, %si
    movw $KERNEL_SECT, %cx
rd_kernel:
    call rd_sect
    addw $512, %bx
    incw %si
    loop rd_kernel

    #不再需要bios功能，开始屏蔽中断
    cli
    #把内核的前512字节移动到0x0000,然后由这512移动其余内核 ds:si->es:di
    cld
    movw $0x1000,%ax
    movw %ax, %ds
    movw $0x0000, %ax
    movw %ax, %es
    xorw %si, %si
    xorw %di, %di
    movw $512>>2, %cx
    rep
    movsl
    #移动gdt到指定位置
    xorw %ax, %ax
    movw %ax, %ds
    movw $gdt, %si
    movw $GDT_ADDR>>4, %ax
    movw %ax, %es
    xorw %di, %di
    movw $GDT_SIZE>>2, %cx
    rep
    movsl
  
enable_a20:
    inb $0x64, %al
    testb $0x2, %al
    jnz enable_a20
    movb $0xdf, %al
    outb %al, $0x64
    
    #载入gdt
    lgdt gdt_48
    #enter pmode
    movl %cr0, %eax
    orl $0x1, %eax
    movl %eax, %cr0
    #在保护模式下跳转到代码起始位置
    ljmp $CODE_SEL, $0x0

rd_sect:
		pushw	%ax
		pushw	%cx
		pushw	%dx
		pushw	%bx

		movw	%si,	%ax		
		xorw	%dx,	%dx
		movw	$18,	%bx	# 18 sectors per track 
					# for floppy disk
		divw	%bx
		incw	%dx
		movb	%dl,	%cl	# cl=sector number
		xorw	%dx,	%dx
		movw	$2,	%bx	# 2 headers per track 
					# for floppy disk
		divw	%bx

		movb	%dl,	%dh	# head
		xorb	%dl,	%dl	# driver
		movb	%al,	%ch	# cylinder
		popw	%bx		# save to es:bx
rp_read:
		movb	$0x1,	%al	# read 1 sector
		movb	$0x2,	%ah
		int	$0x13
		jc	rp_read
		popw	%dx
		popw	%cx
		popw	%ax
		ret
gdt:
    .quad   0x0000000000000000
    .quad   0x00cf9a000000ffff #cs
    .quad   0x00cf92000000ffff #ds
    .quad   0x0000000000000000
    .quad   0x0000000000000000
#gdt的位置与大小，用于lgdt载入
gdt_48:
    .word .-gdt-1
    .long GDT_ADDR

.org 510, 0x90
.word 0xaa55

