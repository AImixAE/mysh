# 在虚拟机中运行

请确保你有 `qemu` 等虚拟机平台

我们需要一个 [linux 内核(bzImage)](https://kernel.org)

解压之后进行编译

```bash
# 需要调整一些设置可以输入这个
make menuconfig
# 编译
make -j$(nproc)
```

随后复制到 `workspaces` 文件夹 _(往后再改名)_

```bash
cp /path/to/bzImage workspace/bzImage
```

记得先使用 `xmake` 编译

我们需要以下文件

-   `build/linux/x86_64/release/static_main`
-   `build/linux/x86_64/release/static_binary_ls`
-   `build/linux/x86_64/release/static_binary_echo`

```bash
xmake b
```

进入 `workspaces` 文件夹, 输入以下命令

```bash
make copy
make
```

编译成功后, 你就可以运行了

```bash
make run
```

