#ifndef EDOS_MULTIBOOT2_H
#define EDOS_MULTIBOOT2_H

#define MB2_HEADER_MAGIC            0xE85250D6
#define MB2_HEADER_ARCHITECTURE_X86 0

#define MB2_HEADER_TAG_END         0
#define MB2_HEADER_TAG_INFO_REQ    1
#define MB2_HEADER_TAG_FRAMEBUFFER 5

#define MB2_TAG_TYPE_END  0
#define MB2_TAG_TYPE_MMAP 6

#define MB2_MAGIC 0x36d76289

#define MB2_MEMORY_AVAILABLE        1
#define MB2_MEMORY_RESERVED         2
#define MB2_MEMORY_ACPI_RECLAIMABLE 3
#define MB2_MEMORY_NVS              4
#define MB2_MEMORY_BADRAM           5

#ifndef __ASSEMBLER__
#include <arch/types.h>
#include <kernel/cdefs.h>

struct mb2_tag_header {
	u32 type;
	u32 size;
} __packed;

struct mb2_info {
	u32 total_size;
	u32 reserved;
	struct mb2_tag_header tags[];
} __packed;

struct mb2_mmap_entry {
	u64 addr;
	u64 len;
	u32 type;
	u32 reserved;
} __packed;

struct mb2_tag_mmap {
	struct mb2_tag_header header;
	u32 entry_size;
	u32 entry_version;
	struct mb2_mmap_entry entries[];
} __packed;

void mb2_process_info(paddr_t mbi_paddr);

#endif

#endif
