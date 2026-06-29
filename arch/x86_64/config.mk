CC      = x86_64-elf-gcc
AS      = x86_64-elf-as
LD      = x86_64-elf-ld

EMULATOR := qemu-system-x86_64 -cdrom $(FINAL_ISO) -serial stdio -no-reboot -boot d
