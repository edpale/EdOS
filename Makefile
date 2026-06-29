ARCH         ?= x86_64
BUILD_DIR    ?= build
KERNEL_BIN    = EdOS
FINAL_ISO     = $(BUILD_DIR)/EdOS-$(ARCH).iso
LINKER_SCRIPT = $(BUILD_DIR)/link.ld

LINKER_TEMPLATE = arch/$(ARCH)/link.ld.S

include arch/$(ARCH)/config.mk

CFLAGS  := -ffreestanding -O2 -Wall -Wextra -Werror -Iinclude -Iarch/$(ARCH)/include \
		   -MMD -MP -mcmodel=kernel -Wstrict-prototypes -Wmissing-prototypes -Wold-style-definition
ASFLAGS := 
LDFLAGS := -T $(LINKER_SCRIPT)
LDLIBS   = $(shell $(CC) $(CFLAGS) -print-libgcc-file-name 2>/dev/null)

SUBDIRS     := arch/$(ARCH) kernel libs
MASTER_OBJS :=

$(foreach dir,$(SUBDIRS), \
    $(eval OBJS :=) \
    $(eval include $(dir)/Makefile) \
    $(eval MASTER_OBJS += $(addprefix $(dir)/,$(OBJS))) \
)

TARGET_OBJS := $(patsubst %,$(BUILD_DIR)/%,$(MASTER_OBJS))
DEPS        := $(TARGET_OBJS:%.o=%.d)

SAFE_RM = @test -n "$(1)" && rm -rf $(1)

ifeq ($(V),1)
  Q =
  REDIR =
else
  Q = @
  REDIR = >/dev/null 2>&1
endif

.PHONY: all clean run

all: $(FINAL_ISO)

iso: $(FINAL_ISO)

$(LINKER_SCRIPT): $(LINKER_TEMPLATE)
	@mkdir -p $(dir $@)
	@echo "  CPP     $<"
	$(Q)$(CC) $(CFLAGS) -E -P -x assembler-with-cpp $< -o $@

$(BUILD_DIR)/$(KERNEL_BIN): $(LINKER_SCRIPT) $(TARGET_OBJS)
	@mkdir -p $(dir $@)
	@echo "  LD      $<"
	$(Q)$(LD) $(LDFLAGS) -o $@ $(TARGET_OBJS) $(LDLIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "  CC      $<"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo "  AS      $<"
	$(Q)$(AS) $(ASFLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.S
	@mkdir -p $(dir $@)
	@echo "  AS      $<"
	$(Q)$(CC) $(CFLAGS) -c $< -o $@

$(FINAL_ISO): $(BUILD_DIR)/$(KERNEL_BIN)
	$(call SAFE_RM,$(BUILD_DIR)/isodir)
	@mkdir -p $(BUILD_DIR)/isodir
	@cp -r isodir/* $(BUILD_DIR)/isodir/
	@cp $(BUILD_DIR)/$(KERNEL_BIN) $(BUILD_DIR)/isodir/boot/$(KERNEL_BIN)
	@echo "  ISO     $@"
	$(Q)grub-mkrescue -o $(FINAL_ISO) $(BUILD_DIR)/isodir $(REDIR)

run: iso
	$(EMULATOR)

clean:
	$(call SAFE_RM,$(BUILD_DIR))

-include $(DEPS)
