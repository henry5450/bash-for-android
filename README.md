# bash-for-android

把 **GNU bash 5.3** 移植到 Android arm64（AArch64）的源码与构建产物。

用 Android NDK (bionic) 交叉编译，**动态链接**。产物只依赖系统自带的
`libc.so` / `libdl.so`，所以仍然是一个文件即可分发。

```
ELF64 AArch64 (PIE)
NEEDED: libdl.so, libc.so
interpreter: /system/bin/linker64
最低 API: 35 (Android 15)
```

已验证：Android 16 / API 36 / arm64-v8a。

## 与上游 bash 的差异

只有 6 个源文件被修改，其余是原样的 bash 5.3 源码。

| 文件 | 改动 |
|---|---|
| `config-top.h` | `DEFAULT_HOME_DIR` / `DEFAULT_TMP_DIR` / `DEFAULT_BASHRC` / `SYS_PROFILE` |
| `pathnames.h.in` | `SYS_PROFILE` 加 `#ifndef` 守卫 |
| `variables.c` | `$HOME` 语义、自动建目录、`TMPDIR`、`$SHELL` |
| `shell.c` | `get_current_user_info()` 的 `/` 兜底 |
| `lib/sh/tmpfile.c` | 临时目录首选 `DEFAULT_TMP_DIR` |
| `lib/sh/eaccess.c` | 绕开 bionic 不支持 `faccessat(AT_EACCESS)` 的问题 |

行为改变摘要：

* `$HOME`：环境里有就继承；未设置 / 空串 / `/` 时用 `/data/local/tmp/home`
* `TMPDIR`：启动时设为 `/data/local/tmp/home/tmp` 并导出（`.bashrc` 里可覆盖）
* `$SHELL`：指向当前运行的 bash 本体，而不是 Android passwd 里的 `/bin/sh`
* `.bashrc`：固定读 `/data/local/tmp/home/.bashrc`，与 `$HOME` 无关；
  `bash -l` 也会读到它
* 上述目录在启动时自动创建（属主身份运行时会把权限放宽到 0777，便于跨 uid 共享）

详细的改造原因、踩过的坑和验证记录见
[`bash-5.3-android-port-summary.txt`](bash-5.3-android-port-summary.txt)。

## 构建

需要 Android NDK。默认路径 `/Application/android-ndk-r29`，可用 `NDK=` 覆盖。

```sh
./cross-build/build-android.sh          # 默认 API 35
./cross-build/build-android.sh 36       # 或指定 API
```

产物是仓库根目录下的 `bash`。

构建脚本里有两个不显然但必须的东西，注释里都写清楚了：

1. `--cache-file=cross-build/android.cache` —— bash 的 configure 靠**运行**测试
   程序判断行为，交叉编译时拿到的默认值在 bionic 上是错的。这个 cache 里的值
   是拿真正的测试程序到真机上跑出来的（见 `android/probe/`）。
2. `make CFLAGS_FOR_BUILD="... -std=gnu17"` —— bash 5.3 在 `CROSS_COMPILING`
   下的构建工具会走到一个在 C23 里非法的 `typedef unsigned char bool`。
   注意这个变量必须传给 make 而不是 configure。

## 安装与使用

```sh
adb push bash /data/local/tmp/
adb shell chmod 755 /data/local/tmp/bash
adb shell /data/local/tmp/bash
```

如果要在 **Termux** 里用，注意 SELinux 默认禁止 `untrusted_app` 执行
`shell_data_file`（即 `/data/local/tmp` 下的文件）。把二进制拷到 Termux 自己的
家目录或其他可执行位置：

```sh
su -c 'cp /data/local/tmp/bash /data/data/com.termux/files/home/bash'
```

## 配置文件

仓库里的 [`android/bashrc`](android/bashrc) 是部署到
`/data/local/tmp/home/.bashrc` 的参考版本：PATH 补齐、历史记录、提示符、
别名、以及让 `su` 起的 shell 仍是 bash 的包装函数。

## 已知限制

* 静态链接没有意义（Android 上 libc 永远存在），动态链接还保留了 `dlopen`。
* here-document 在 bash 5.3 里小于约 64KB 时走进程内管道，不落盘；
  进程替换走 `/dev/fd`。所以 `TMPDIR` 只在较大的 here-doc 时才真正用到。
* 非交互 shell（`bash script.sh`、管道输入）不会读 `.bashrc` —— 这是 bash
  原生行为。只有 stdin 是套接字时（adb/ssh）的 `bash -c` 例外。

## License

bash 本身是 **GPLv3**，本仓库的修改同样遵循其许可，见 [`COPYING`](COPYING)。
