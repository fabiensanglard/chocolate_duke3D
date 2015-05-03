#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([Chocolate Duke3D],
        [1.0],
        [https://github.com/fabiensanglard/chocolate_duke3D/issues])
AC_CONFIG_SRCDIR([.])

AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([foreign])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB
case "$host" in
  *cygwin*|*mingw*)
    AC_CHECK_TOOL([WINDRES], [windres], [])
    ;;
esac
AM_CONDITIONAL([WITH_WIN_ICON], [test "$WINDRES" != ""])

# Checks for libraries.
PKG_CHECK_MODULES([SDL], [sdl], [], [
    AC_CHECK_LIB([SDL], [main], [], [exit 1])
])
PKG_CHECK_MODULES([SDL_MIXER], [SDL_mixer], [], [
    AC_CHECK_LIB([SDL_mixer], [main], [], [exit 1])
])

dnl Compiler flags
CFLAGS_WARNINGS="-Wall -Wno-pointer-sign -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast \
-Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-result"
CFLAGS="${CFLAGS_WARNINGS} -fno-strict-aliasing -fno-aggressive-loop-optimizations -DPLATFORM_UNIX $(pkg-config --cflags SDL_mixer) ${CFLAGS}"
LDFLAGS="$(pkg-config --libs sdl) $(pkg-config --libs SDL_mixer) ${LDFLAGS}"

# Checks for header files.
AC_CHECK_HEADERS([assert.h enet/enet.h])

AC_CONFIG_FILES([Engine/src/Makefile
                 Game/src/Makefile
                 Game/src/audiolib/Makefile
                 Game/src/midi/Makefile
                 Game/Makefile
                 Makefile])
AC_OUTPUT
