#include <arch/gdt.h>
#include <kernel/cdefs.h>

static u64 gdt[NGDT_ENTRIES] __aligned(16) = {
	[GDT_NULL] = 0x0,
	[GDT_KERN_CODE] = GDT_ENTRY(0x0, 0xFFFFF, SEG_DESC_ACC_CODE,
				    SEG_DESC_FLAGS_CODE64),
	[GDT_KERN_DATA] = GDT_ENTRY(0x0, 0xFFFFF, SEG_DESC_ACC_DATA,
				    SEG_DESC_FLAGS_DATA),
	[GDT_USER_CODE] = GDT_ENTRY(0x0, 0xFFFFF, SEG_DESC_ACC_CODE |
				    SEG_DESC_USER, SEG_DESC_FLAGS_CODE64),
	[GDT_USER_DATA] = GDT_ENTRY(0x0, 0xFFFFF, SEG_DESC_ACC_DATA |
				    SEG_DESC_USER, SEG_DESC_FLAGS_DATA),
};

static struct gdt_ptr gdtr = {
	.limit = sizeof(gdt) - 1,
	.base = (u64)&gdt,
};

void gdt_init(void)
{
	asm volatile ("lgdt %0\n"
		      "xor %%ax, %%ax\n"
		      "mov %%ax, %%ss\n"
		      "mov %%ax, %%ds\n"
		      "mov %%ax, %%es\n"
		      "mov %%ax, %%fs\n"
		      "mov %%ax, %%gs\n"
		      "pushq %1\n"
		      "lea 1f(%%rip), %%rax\n"
		      "pushq %%rax\n"
		      "lretq\n"
		      "1:"
		      :
		      : "m"(gdtr), "i"(SEG_SEL_KERN_CODE)
		      : "rax", "memory");
}
