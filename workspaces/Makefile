.PHONY: all clean run copy

all: mysh.cpio
	@echo "All done!"

mysh.cpio:
	(cd initfs && find . -print | cpio -ov -H newc) > mysh.cpio

clean:
	rm -f mysh.cpio

copy: ../build/linux/x86_64/release/static_main ../build/linux/x86_64/release/static_binary_ls ../build/linux/x86_64/release/static_binary_echo
	mkdir -p initfs
	mkdir -p initfs/bin
	cp ../build/linux/x86_64/release/static_main initfs/init
	cp ../build/linux/x86_64/release/static_binary_ls initfs/bin/ls
	cp ../build/linux/x86_64/release/static_binary_echo initfs/bin/echo

run: mysh.cpio bzImage
	qemu-system-x86_64 \
		-kernel ./bzImage \
		-initrd ./mysh.cpio \
		-append "root=/dev/rom rw"
