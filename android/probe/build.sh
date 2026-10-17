#!/bin/bash
NDKBIN=/Application/android-ndk-r29/toolchains/llvm/prebuilt/linux-x86_64/bin
CC=$NDKBIN/aarch64-linux-android35-clang
DEFS="-D_GNU_SOURCE=1 -DHAVE_UNISTD_H=1 -DHAVE_SYS_WAIT_H=1 -DHAVE_SYS_TIME_H=1 \
-DHAVE_SYS_RESOURCE_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_DIRENT_H=1 -DHAVE_LOCALE_H=1 \
-DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_POSIX_SIGNALS=1 -DHAVE_SETLOCALE=1 \
-DHAVE_STRCOLL=1 -DHAVE_MKFIFO=1 -DGETPGRP_VOID=1"
rm -rf android/probe/bin; mkdir -p android/probe/bin
for f in android/probe/src/*.c; do
  n=$(basename "$f" .c)
  if ! $CC $DEFS -O0 -w -o "android/probe/bin/$n" "$f" 2>"android/probe/bin/$n.buildlog"; then
    echo "BUILDFAIL $n"          # 构建失败 -> 对应 autoconf 的 action-if-false
    continue
  fi
  echo "OK        $n"
done
