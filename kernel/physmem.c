#include <arch/param.h>
#include <kernel/bug.h>
#include <kernel/panic.h>
#include <kernel/physmem.h>
#include <kernel/string.h>
#include <kernel/utils.h>

#define MAX_PHYSMEM_REGIONS 32

struct physmem_region {
	paddr_t start;
	paddr_t end;
};

struct physmem_list {
	size_t regions_count;
	size_t regions_cap;
	struct physmem_region *regions;
};

static struct physmem_region prealloced_memory_regions[MAX_PHYSMEM_REGIONS];
static struct physmem_list mem_avail = {
	.regions = prealloced_memory_regions,
	.regions_cap = MAX_PHYSMEM_REGIONS,
};

static void merge_upper_regions(struct physmem_list *list, size_t index)
{
	struct physmem_region *indexed = &list->regions[index];
	size_t i = index + 1;

	while (i < list->regions_count &&
	       list->regions[i].start <= indexed->end) {
		if (list->regions[i].end > indexed->end) {
			indexed->end = list->regions[i].end;
			break;
		}
		i++;
	}
	memmove(indexed + 1, &list->regions[i],
		(list->regions_count - i) * sizeof(*list->regions));
	list->regions_count -= (i - index - 1);
}

static result_t insert_region_at(struct physmem_list *list,
				 paddr_t start, paddr_t end, size_t index)
{
	if (list->regions_count >= list->regions_cap)
		return RES_OVERFLOW;

	BUG_ON(index > list->regions_count);

	memmove(&list->regions[index + 1], &list->regions[index],
		(list->regions_count - index) * sizeof(*list->regions));
	list->regions[index].start = start;
	list->regions[index].end = end;
	list->regions_count++;
	return RES_OK;
}

/*
 * Inserts a region in to array, keeps it sorted. On overlaps, regions are
 * merged.
 */
static result_t insert_region(struct physmem_list *list,
			      paddr_t start, paddr_t end)
{
	for (size_t i = 0; i < list->regions_count; i++) {
		struct physmem_region *curr = &list->regions[i];

		if (start > curr->end)
			continue;

		if (end < curr->start)
			return insert_region_at(list, start, end, i);

		if (start < curr->start)
			curr->start = start;

		if (end > curr->end) {
			curr->end = end;
			merge_upper_regions(list, i);
		}
		return RES_OK;
	}

	return insert_region_at(list, start, end, list->regions_count);
}

static result_t remove_region(struct physmem_list *list,
			      paddr_t start, paddr_t end)
{
	size_t si = 0, ei;

	BUG_ON(start >= end);

	while (si < list->regions_count &&
	       start > list->regions[si].start) {
		paddr_t curr_end = list->regions[si].end;

		if (start < curr_end) {
			list->regions[si].end = start;
			if (end < curr_end)
				return insert_region_at(list, end, curr_end,
							si + 1);
		}
		si++;
	}

	ei = si;
	while (ei < list->regions_count &&
	       end > list->regions[ei].start) {

		if (end < list->regions[ei].end) {
			list->regions[ei].start = end;
			break;
		}
		ei++;
	}

	memmove(&list->regions[si], &list->regions[ei],
		(list->regions_count - ei) * sizeof(*list->regions));
	list->regions_count -= ei - si;
	return RES_OK;
}

void physmem_add_region(paddr_t start, paddr_t end)
{
	result_t res;

	/* filter out frame 0 */
	if (start == 0)
		start = PAGE_SIZE;

	start = roundup2(start, PAGE_SIZE);
	end = rounddown2(end, PAGE_SIZE);
	if (start >= end)
		return;

	res = insert_region(&mem_avail, start, end);
	if (res)
		panic("physmem: too many hardware regions (raise MAX_PHYSMEM_REGIONS)");
}

void physmem_exclude_region(paddr_t start, paddr_t end)
{
	result_t res;

	BUG_ON(start > end);
	start = rounddown2(start, PAGE_SIZE);
	end = roundup2(end, PAGE_SIZE);

	res = remove_region(&mem_avail, start, end);
	if (res)
		panic("physmem: too many hardware regions (raise MAX_PHYSMEM_REGIONS)");
}

static result_t alloc_pages_in_range(struct physmem_list *list,
				     paddr_t range_start, paddr_t range_end,
				     size_t n, paddr_t *out)
{
	paddr_t pages_size;

	BUG_ON(range_start >= range_end);
	BUG_ON(!is_aligned(range_start, PAGE_SIZE));
	BUG_ON(!is_aligned(range_end, PAGE_SIZE));
	if (check_mul_overflow(n, PAGE_SIZE, &pages_size))
		return RES_INVALID_ARG;
	if (pages_size > range_end - range_start)
		return RES_INVALID_ARG;

	for (size_t i = 0; i < list->regions_count; i++) {
		struct physmem_region *curr = &list->regions[i];
		paddr_t alloc_start, alloc_end;

		if (curr->start >= range_end)
			break;
		if (curr->end <= range_start)
			continue;

		alloc_start = max(curr->start, range_start);
		if (check_add_overflow(alloc_start, pages_size, &alloc_end))
			break;
		if (alloc_end > range_end)
			break;

		if (alloc_end <= curr->end) {
			result_t res = remove_region(list, curr->start,
						     alloc_end);
			if (res == RES_OK)
				*out = alloc_start;
			return res;
		}
	}

	return RES_NO_MEMORY;
}

result_t physmem_alloc_pages_in_range(paddr_t range_start, paddr_t range_end,
				      size_t n, paddr_t *out)
{
	return alloc_pages_in_range(&mem_avail, range_start, range_end, n, out);
}
