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

#ifndef __ASSEMBLER__
#include <arch/types.h>


void mb2_process_mbi(paddr_t mbi_paddr);

#endif

#endif
