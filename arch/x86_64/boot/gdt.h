#ifndef EDOS_X86_64_GDT_H
#define EDOS_X86_64_GDT_H

#include <kernel/const.h>

#define GDT_NULL      0
#define GDT_KERN_CODE 1
#define GDT_KERN_DATA 2
#define GDT_USER_CODE 3
#define GDT_USER_DATA 4
#define GDT_TSS       5
#define NGDT_ENTRIES  7

#define SEG_DESC_SHIFT 3
#define SEG_DESC_SIZE  (1 << SEG_DESC_SHIFT)

#define SEG_SEL_KERN_CODE (GDT_KERN_CODE << SEG_DESC_SHIFT)
#define SEG_SEL_KERN_DATA (GDT_KERN_DATA << SEG_DESC_SHIFT)
#define SEG_SEL_USER_CODE (GDT_USER_CODE << SEG_DESC_SHIFT)
#define SEG_SEL_USER_DATA (GDT_USER_DATA << SEG_DESC_SHIFT)

#define SEG_DESC_ACCESSED        0x01
#define SEG_DESC_CODE_READABLE   0x02
#define SEG_DESC_DATA_WRITABLE   0x02
#define SEG_DESC_CODE_CONFORMING 0x04
#define SEG_DESC_EXECUTABLE      0x08
#define SEG_DESC_S               0x10
#define SEG_DESC_DPL(_dpl)       ((_dpl) << 5)
#define SEG_DESC_USER            (SEG_DESC_DPL(3))
#define SEG_DESC_PRESENT         0x80

#define SEG_DESC_LONG_CODE 0x2
#define SEG_DESC_DB        0x4
#define SEG_DESC_G         0x8

#define SEG_DESC_ACC_CODE (SEG_DESC_ACCESSED | SEG_DESC_CODE_READABLE | \
			   SEG_DESC_EXECUTABLE | SEG_DESC_S | SEG_DESC_PRESENT)
#define SEG_DESC_ACC_DATA (SEG_DESC_ACCESSED | SEG_DESC_DATA_WRITABLE | \
			   SEG_DESC_S | SEG_DESC_PRESENT)

#define SEG_DESC_FLAGS_DATA (SEG_DESC_DB | SEG_DESC_G)

#define SEG_DESC_FLAGS_CODE32 SEG_DESC_FLAGS_DATA
#define SEG_DESC_FLAGS_CODE64 (SEG_DESC_LONG_CODE | SEG_DESC_G)

#ifndef __ASSEMBLER__
#include <kernel/types.h>
#include <kernel/cdefs.h>

struct gdt_ptr {
	u16 limit;
	u64 base;
} __packed;

void gdt_init(void);

#endif

#define GDT_ENTRY(_base, _limit, _access, _flags)   \
	((ASMT(_limit, u64)  & 0xFFFF)            | \
	 ((ASMT(_base, u64)  & 0xFFFFFF)   << 16) | \
	 (ASMT(_access, u64)               << 40) | \
	 ((ASMT(_limit, u64) & 0xF0000)    << 32) | \
	 (ASMT(_flags, u64)                << 52) | \
	 ((ASMT(_base, u64)  & 0xFF000000) << 32))

#endif
