# My Shell

节选自本项目 [`README.md`](/README.md)

## 在虚拟机上运行

请确保你有 `qemu` 等虚拟机平台

我们需要一个 [linux 内核(bzImage)](https://kernel.org) 并且复制到 `workspaces` 文件夹

进入 `workspaces` 文件夹, 输入以下命令

```bash
make copy
make
```

然后, 你就可以运行了

```bash
make run
```
