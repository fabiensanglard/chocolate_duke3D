/**
 @file  types.h
 @brief type definitions for ENet
*/
#ifndef __ENET_TYPES_H__
#define __ENET_TYPES_H__

#ifdef _WIN32
   #include "../../windows/inttypes.h"
#else
   #include <inttypes.h>
#endif

typedef uint8_t enet_uint8;       /**< unsigned 8-bit type  */
typedef uint16_t enet_uint16;     /**< unsigned 16-bit type */
typedef unsigned int enet_uint32;      /**< unsigned 32-bit type */

#endif /* __ENET_TYPES_H__ */

