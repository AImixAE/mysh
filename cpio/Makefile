.PHONY: clean clean-all copy_lib copy_syslib copy_tools copy_tools_lib chrpath

all: initfs initfs/init copy_lib copy_syslib copy_tools copy_tools_lib chrpath mysh.cpio
	@echo "All Done!"

mysh.cpio: initfs initfs/init
	(cd $< && find . -print | cpio -ov -H newc) > mysh.cpio

initfs:
	mkdir -p initfs
	mkdir -p initfs/usr/bin
	mkdir -p initfs/usr/lib
	cd initfs; (cd usr; ln -s lib lib64); ln -s usr/lib lib; ln -s usr/lib64 lib64; ln -s usr/bin bin

initfs/init: ../build/main
	cp $< initfs/init

../build/main:
	cd ..; cmake -G Ninja -B build
	cd ../build; ninja

copy_lib:
	cp ../build/lib*.so initfs/usr/lib

copy_syslib:
	@echo "Tip: 如果出错, 请替换里面的库文件路径"
	cp /usr/lib/libreadline.so.8 /usr/lib/libc.so.6 /usr/lib/libncursesw.so.6 /usr/lib64/ld-linux-x86-64.so.2 initfs/usr/lib

copy_tools: initfs/usr/bin
	cp /bin/ls /bin/echo /bin/touch /bin/cat /bin/mkdir /bin/cp /bin/mv /bin/bash initfs/usr/bin

copy_tools_lib:
	cp /usr/lib/libcap.so.2 /usr/lib/libacl.so.1 /usr/lib/libattr.so.1 initfs/usr/lib

chrpath: initfs/init
	cd initfs; patchelf --force-rpath --set-rpath ./usr/lib init; ldd init

seerpath: initfs/init
	cd initfs; ldd init

run: mysh.cpio bzImage
	qemu-system-x86_64 \
		-kernel ./bzImage \
		-initrd ./mysh.cpio \
		-append "root=/dev/rom rw"

clean:
	rm -f mysh.cpio

clean-all:
	rm -rf mysh.cpio initfs
