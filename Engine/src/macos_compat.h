//
//  macos_compat.h
//  Duke3D
//
//  Created by fabien sanglard on 12-12-12.
//  Copyright (c) 2012 fabien sanglard. All rights reserved.
//

#ifndef Duke3D_macos_compat_h
#define Duke3D_macos_compat_h

#define PLATFORM_SUPPORTS_SDL

#define __far
#define __interrupt
#define interrupt
#define far
#define kmalloc(x) malloc(x)
#define kkmalloc(x) malloc(x)
#define kfree(x) free(x)
#define kkfree(x) free(x)

#ifdef FP_OFF
#undef FP_OFF
#endif

#define FP_OFF(x) ((long) (x))

#ifndef max
#define max(x, y)  (((x) > (y)) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)  (((x) < (y)) ? (x) : (y))
#endif

#include <inttypes.h>
#define __int64 int64_t

#define O_BINARY 0

#define UDP_NETWORKING 1

#define PLATFORM_MACOSX 1

#define SOL_IP SOL_SOCKET
#define IP_RECVERR  SO_BROADCAST

#define stricmp strcasecmp

#endif
