# My Shell

`My Shell` 简称 `mysh`, 支持调用系统命令

我们为 `mysh` 提供了 `echo` 等简单工具, 使调试更方便

我们也做了 `init` 支持, 使其能在 `linux` 内核上运行

## 编译

```bash
xmake b
```

你会得到很多产物, 让我们来一一解释一下

-   `binary_*`: 动态二进制简单工具
-   `static_binary_*`: 静态二进制简单工具
-   `shared_*`: 动态二进制程序
-   `static_*`: 静态二进制程序
-   `libshared_*.so`: 动态文件
-   `libstatic_*.a`: 静态文件

## 在虚拟机中运行

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

简略说明，详细在这里 👉 [RunOnVM](doc/RunOnVM.md)

