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
    AC_CHECK_LIB([SDL], [main], [
        SDL_CFLAGS="-D_GNU_SOURCE=1 -D_REENTRANT -I/usr/include/SDL"
        LIBS="$LIBS -lSDL"
        ], [exit 1])
])
PKG_CHECK_MODULES([SDL_MIXER], [SDL_mixer], [], [
    AC_CHECK_LIB([SDL_mixer], [main], [
        LIBS="$LIBS -lSDL_mixer"
        ], [exit 1])
])

dnl Compiler flags
CFLAGS="-Wall \
-Wno-pointer-sign -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast \
-Wno-parentheses -Wno-maybe-uninitialized -Wno-unused-but-set-variable \
-Wno-unused-function -Wno-unused-result \
-fno-strict-aliasing -fno-aggressive-loop-optimizations \
-DPLATFORM_UNIX $SDL_CFLAGS $CFLAGS"


# Checks for header files.
AC_CHECK_HEADERS([assert.h enet/enet.h])

AC_CONFIG_FILES([Engine/src/Makefile
                 Game/src/Makefile
                 Game/src/audiolib/Makefile
                 Game/src/midi/Makefile
                 Game/Makefile
                 Makefile])
AC_OUTPUT
