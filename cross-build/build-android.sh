#!/bin/sh
# build-android.sh -- cross-compile bash 5.3 for Android arm64 (NDK / bionic)
#
# Usage:  ./cross-build/build-android.sh [API_LEVEL]      (default: 35)
#
# Produces: ./bash   (ELF64 AArch64 PIE, dynamically linked against bionic)
#   NEEDED: libdl.so, libc.so   -- both are system libraries on every Android
#   device, so the result is still a single self-contained file.
#
# ---------------------------------------------------------------------------
# Two things here are NOT obvious and will silently break a rebuild:
#
# 1) --cache-file=cross-build/android.cache
#    bash's configure probes ~30 behaviours by RUNNING test programs.  Under
#    --host they cannot run, so autoconf falls back to conservative defaults
#    that are wrong on bionic.  The cache holds values measured by running the
#    actual test programs on a real device; see android/probe/ for the harness and
#    the raw exit codes.  Two examples of why guessing is not good enough:
#      * bash_cv_getcwd_malloc=yes  (bionic getcwd(NULL,0) DOES allocate; the
#        autoconf default of "no" makes bash compile its own getcwd fallback)
#      * bash_cv_sys_siglist=yes    (bionic has sys_siglist, typed const)
#
# 2) make CFLAGS_FOR_BUILD="... -std=gnu17"
#    When CROSS_COMPILING is defined, the host-side build tools (mkbuiltins,
#    mksignatures, ...) include buildconf.h rather than config.h, and
#    buildconf.h does not define HAVE_STDBOOL_H.  bashansi.h therefore falls
#    back to `typedef unsigned char bool;`, which is a hard error when the
#    build-host compiler defaults to C23 (gcc 15+ does, `bool` is a keyword).
#    Target compiles are unaffected: they use config.h, which does define
#    HAVE_STDBOOL_H, and clang 21 still defaults to C17.
#
#    CFLAGS_FOR_BUILD must be passed to make, NOT to configure: configure.ac
#    AC_ARG_VAR()s it, so setting it in the environment only on a re-run trips
#    autoconf's "changes in the environment can compromise the build" guard.
# ---------------------------------------------------------------------------

set -e

API=${1:-35}
NDK=${NDK:-/Application/android-ndk-r29}
HOST_TAG=linux-x86_64
NDKBIN=$NDK/toolchains/llvm/prebuilt/$HOST_TAG/bin

CC=$NDKBIN/aarch64-linux-android$API-clang
[ -x "$CC" ] || { echo "no such compiler: $CC" >&2; exit 1; }

export CC
export AR=$NDKBIN/llvm-ar
export RANLIB=$NDKBIN/llvm-ranlib
export STRIP=$NDKBIN/llvm-strip
export NM=$NDKBIN/llvm-nm

./configure \
	--build=x86_64-pc-linux-gnu \
	--host=aarch64-linux-android \
	--cache-file=cross-build/android.cache \
	--disable-nls \
	--without-bash-malloc

# -DCROSS_COMPILING is part of the default value, so it must be repeated here.
make -j"$(nproc)" CFLAGS_FOR_BUILD="-g -DCROSS_COMPILING -std=gnu17"

echo
echo "built: $(pwd)/bash"
$STRIP --version >/dev/null 2>&1 || true
echo "install: adb push bash /data/local/tmp/ && adb shell chmod 755 /data/local/tmp/bash"
