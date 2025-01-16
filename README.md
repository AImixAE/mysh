# My Shell

`My Shell` 简称 `mysh`, 支持调用系统命令

我们为 `mysh` 提供了 `echo` 等简单工具, 使调试更方便

我们也做了 `init` 支持, 使其能在 `linux` 内核上运行

## 编译

```bash
cmake -G Ninja -B build
cd build
ninja
```

你会得到很多产物, 让我们来一一解释一下

-   `lib*.so`: 动态库文件
-   `main`: 主程序入口

## 在虚拟机中运行

请确保你有 `qemu` 等虚拟机平台

我们需要一个 [linux 内核(bzImage)](https://kernel.org) 并且复制到 `workspaces` 文件夹

进入 `workspaces` 文件夹, 输入以下命令

```bash
./build all
```

然后, 你就可以运行了

```bash
./build run
```

简略说明，详细在这里 👉 [RunOnVM](doc/RunOnVM.md)

