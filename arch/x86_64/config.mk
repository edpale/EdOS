CC      = x86_64-elf-gcc
AS      = x86_64-elf-as
LD      = x86_64-elf-ld

CFLAGS += -mcmodel=kernel -mno-red-zone -mgeneral-regs-only

EMULATOR := qemu-system-x86_64 -cdrom $(FINAL_ISO) -serial stdio -no-reboot -boot d
