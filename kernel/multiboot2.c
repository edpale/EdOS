#include <arch/boot.h>
#include <kernel/multiboot2.h>
#include <kernel/printf.h>
#include <kernel/utils.h>

static inline struct mb2_tag_header *mb2_next_tag(struct mb2_tag_header *tag)
{
	return (struct mb2_tag_header *)((u8 *)tag + roundup2(tag->size, 8));
}

static void mb2_handle_mmap(struct mb2_tag_mmap *tag)
{
	for (struct mb2_mmap_entry *i = tag->entries;
	     (u8 *)i - (u8 *)tag < tag->header.size;
	     i = (struct mb2_mmap_entry *)((u8 *)i + tag->entry_size)) {
		kprintf("Mem area:\nstart: %llx\nlen: %llx\ntype %x\n\n",
			i->addr, i->len, i->type);
	}
}

void mb2_process_info(paddr_t mbi_paddr)
{
	struct mb2_info *info = boot_pa_to_va(mbi_paddr);

	for (struct mb2_tag_header *i = info->tags;
	     (u8 *)i - (u8 *)info < info->total_size;
	     i = mb2_next_tag(i)) {
		switch (i->type) {
		case MB2_TAG_TYPE_MMAP:
			mb2_handle_mmap((struct mb2_tag_mmap *)i);
			break;
		case MB2_TAG_TYPE_END:
			goto end;
		}
	}
end:
}
