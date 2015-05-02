#!/bin/sh

if [ -e "/usr/local/include/enet/enet.h" ]; then
   CPPFLAGS="${CPPFLAGS} -D__SYSTEM_ENET"
   CFLAGS="${CFLAGS} -I/usr/local/include"
elif [ -e "/usr/include/enet/enet.h" ]; then
   CPPFLAGS="${CPPFLAGS} -D__SYSTEM_ENET"
fi

export PKG_CONFIG_PATH="/usr/lib32/pkgconfig:/usr/lib/i386-linux-gnu/pkgconfig:${PKG_CONFIG_PATH}"
export CFLAGS="${CFLAGS}"
export CPPFLAGS="${CPPFLAGS}"
export LDFLAGS="-L/usr/lib32 -L/usr/lib/i386-linux-gnu ${LDFLAGS}"

pkg-config --libs sdl 2>/dev/null >/dev/null
if [ `echo $?` -ne 0 ]; then
   echo "\`sdl' is missing"
   exit 1
fi

pkg-config --libs SDL_mixer 2>/dev/null >/dev/null
if [ `echo $?` -ne 0 ]; then
   echo "\`SDL_mixer' is missing"
   exit 1
fi

if [ `nproc` -gt 1 ]; then
   NPROC=-j`nproc`
fi

echo "PKG_CONFIG_PATH: ${PKG_CONFIG_PATH}"
echo "CFLAGS: ${CFLAGS}"
echo "CPPFLAGS: ${CPPFLAGS}"
echo "LDFLAGS: ${LDFLAGS}"
echo ""
echo "running \`make ${NPROC} || exit 1'"
echo ""
make ${NPROC} || exit 1
echo ""
echo "Done."
