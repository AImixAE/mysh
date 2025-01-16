#!/bin/bash

main () {
    case "$1" in
        all)
            $0 initfs
            $0 initfs_link
            $0 copy
            $0 copy_link
            $0 copy_tools
            $0 copy_lib
            $0 chrpath
            $0 mkcpio

            echo "All Done!"
            ;;

        initfs)
            mkdir -p initfs
            mkdir -p initfs/{bin,usr/lib}
            ;;

        initfs_link)
            (cd initfs && (cd usr && ln -s lib lib64) && ln -s usr/lib lib && ln -s usr/lib64 lib64)
            ;;

        copy)
            cp ../build/main initfs/init
            cp ../build/lib*.so initfs/usr/lib    
            ;;

        copy_tools)
            cp /bin/ls /bin/echo initfs/bin
            ;;

        copy_lib)
            cp /usr/lib/libreadline.so.8 /usr/lib/libcap.so.2 /usr/lib/libc.so.6 /usr/lib/libncursesw.so.6 /usr/lib64/ld-linux-x86-64.so.2 initfs/usr/lib
            ;;

        chrpath)
            (cd initfs && chrpath -r ./usr/lib init && ldd init)
            echo "请在 initfs 下查看 init"
            ;;

        seerpath)
            (cd initfs && ldd init)
            ;;

        mkcpio)
            (cd initfs && find . -print | cpio -ov -H newc) > mysh.cpio
            ;;

        seecpio)
            cpio -itv < mysh.cpio
            ;;

        clean)
            rm -rf initfs
            rm -f mysh.cpio
            ;;

        run)
            qemu-system-x86_64 \
                -kernel ./bzImage \
                -initrd ./mysh.cpio \
                -append "root=/dev/rom rw"
            ;;
    esac
}

for i in "$@"; do
    main ${i}
done
