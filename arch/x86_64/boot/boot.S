#include <arch/cpufeatures.h>
#include <arch/cpuflags.h>
#include <arch/param.h>
#include <arch/pte.h>
#include <arch/vmparam.h>
#include <kernel/multiboot2.h>

#include "gdt.h"

.set MB2_HEADER_LEN, mb2_header_end - mb2_header_start

.section .multiboot2, "a"
.align 8
mb2_header_start:
.long MB2_HEADER_MAGIC
.long MB2_HEADER_ARCHITECTURE_X86
.long MB2_HEADER_LEN
.long -(MB2_HEADER_MAGIC + MB2_HEADER_ARCHITECTURE_X86 + MB2_HEADER_LEN)

.align 8
.short MB2_HEADER_TAG_INFO_REQ
.short 0
.long  12
.long  MB2_TAG_TYPE_MMAP

.align 8
.short MB2_HEADER_TAG_END
.short 0
.long  8
mb2_header_end:

.section .boot, "ax"
.code32
.global _start
.type _start, @function
_start:
	/* Init stack */
	mov $KERN_TO_PHYS(boot_stack_top), %esp

	push %eax
	push %ebx

	call check_cpuid

	call check_long_mode

	call init_page_tables

	call enable_pae

	/* Load CR3 with PML4 physical address */
	movl $KERN_TO_PHYS(boot_pml4), %eax
	mov %eax, %cr3

	call enable_long_mode

	call enable_paging

	lgdt KERN_TO_PHYS(gdt_ptr)

	pop %esi
	pop %edi

	ljmp $0x8, $KERN_TO_PHYS(long_mode_start)
end:
	cli
1:	hlt
	jmp 1b
.size _start, . - _start

.type check_long_mode, @function
check_long_mode:
	mov $0x80000000, %eax
	cpuid
	cmp $0x80000001, %eax
	jb end

	mov $0x80000001, %eax
	cpuid
	test $FEATURE_AMD_LM, %edx
	jz end

	ret
.size check_long_mode, . - check_long_mode

.type check_cpuid, @function
check_cpuid:
	pushfl
	pop %eax

	mov %eax, %ecx
	xor $RFLAGS_ID, %eax

	push %eax
	popfl
	pushfl
	pop %eax

	push %ecx
	popfl

	xor %eax, %ecx
	jz end

	ret
.size check_cpuid, . - check_cpuid

.type init_page_tables, @function
init_page_tables:
	/* PML4[0] -> PDPT_LOW */
	movl $KERN_TO_PHYS(boot_pdpt_low), %eax
	orl $(PG_V | PG_RW), %eax
	movl %eax, KERN_TO_PHYS(boot_pml4) + 0 * PML4E_SIZE

	/* PML4[511] -> PDPT_HIGH */
	movl $KERN_TO_PHYS(boot_pdpt_high), %eax
	orl $(PG_V | PG_RW), %eax
	movl %eax, KERN_TO_PHYS(boot_pml4) + \
		PML4_INDEX(KERN_BASE_VIRT) * PML4E_SIZE

	/* PDPT_LOW[0..3] -> PD 0..3 */
	leal KERN_TO_PHYS(boot_pdpt_low), %edx

	leal KERN_TO_PHYS(boot_pds), %eax
	orl $(PG_V | PG_RW), %eax

	movl $(BOOT_IDMAP_SIZE >> PDPE_MAP_SHIFT), %ecx

1:
	movl %eax, (%edx)

	addl $PAGE_SIZE, %eax
	addl $PDPE_SIZE, %edx
	loop 1b

	/* PDPT_HIGH[-2,-1] -> PD 0,1 */
	leal KERN_TO_PHYS(boot_pdpt_high) + \
		PDPT_INDEX(KERN_BASE_VIRT) * PDPE_SIZE, %edx

	leal KERN_TO_PHYS(boot_pds), %eax
	orl $(PG_V | PG_RW), %eax

	movl $(KERN_REG_SIZE >> PDPE_MAP_SHIFT), %ecx

1:
	movl %eax, (%edx)

	addl $PAGE_SIZE, %eax
	addl $PDPE_SIZE, %edx
	loop 1b

	/* Fill up PD */
	leal KERN_TO_PHYS(boot_pds), %edx
	movl $(NPDE * (BOOT_IDMAP_SIZE >> PDPE_MAP_SHIFT)), %ecx

	movl $(PG_V | PG_RW | PG_PS), %eax
1:
	movl %eax, (%edx)

	addl $PDE_MAP_SIZE, %eax
	addl $PDE_SIZE, %edx
	loop 1b

	ret
.size init_page_tables, . - init_page_tables

.type enable_paging, @function
enable_paging:
	movl %cr0, %eax
	orl $CR0_PG, %eax
	movl %eax, %cr0

	ret
.size enable_paging, . - enable_paging

.type enable_pae, @function
enable_pae:
	movl %cr4, %eax
	orl $CR4_PAE, %eax
	movl %eax, %cr4

	ret
.size enable_pae, . - enable_pae

.type enable_long_mode, @function
enable_long_mode:
	movl $MSR_EFER, %ecx
	rdmsr
	orl $EFER_LME, %eax
	wrmsr

	ret
.size enable_long_mode, . - enable_long_mode

.section .text
.code64
long_mode_start:
	mov $0, %ax
	mov %ax, %ss
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	movabs $boot_stack_top, %rsp

	xor %ebp, %ebp
	mov %esi, %esi
	mov %edi, %edi
	movabs $kmain, %rax
	call *%rax

	cli
1:	hlt
	jmp 1b
.size long_mode_start, . - long_mode_start

.section .data
.align 8
gdt_start:
	.quad 0
	.quad GDT_ENTRY(0x0, 0xFFFFF, SEG_DESC_ACC_CODE, SEG_DESC_FLAGS_CODE64)
	.quad GDT_ENTRY(0x0, 0xFFFFF, SEG_DESC_ACC_DATA, SEG_DESC_FLAGS_DATA)
gdt_end:

gdt_ptr:
	.short gdt_end - gdt_start - 1
	.long KERN_TO_PHYS(gdt_start)

.section .bss
.align PAGE_SIZE
boot_pml4:      .skip PAGE_SIZE
boot_pdpt_low:  .skip PAGE_SIZE
boot_pdpt_high: .skip PAGE_SIZE
boot_pds:       .skip PAGE_SIZE * (BOOT_IDMAP_SIZE >> PDPE_MAP_SHIFT)

.align 16
.skip KERN_STACK_SIZE
boot_stack_top:
