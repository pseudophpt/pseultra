/*
 * pseultra/include/util.h
 * Utility functions
 * 
 * (C) pseudophpt 2018
 */


#ifndef UTIL_H_GUARD
#define UTIL_H_GUARD

#define BE_TO_LE32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) & 0xff000000) >> 24))
#define LE_TO_BE32(x) ((((x) & 0xff) << 24) | (((x) & 0xff00) << 8) | (((x) & 0xff0000) >> 8) | (((x) & 0xff000000) >> 24))

#define BE_TO_LE16(x) ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8)) 
#define LE_TO_BE16(x) ((((x) & 0xff) << 8) | (((x) & 0xff00) >> 8))

#endif
