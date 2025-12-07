#ifndef CONFIGMS_H_INCLUDED
#define CONFIGMS_H_INCLUDED

/* The number of bytes in a double.  */
#define SIZEOF_DOUBLE 8

/* The number of bytes in a float.  */
#define SIZEOF_FLOAT 4

/* The number of bytes in a int.  */
#define SIZEOF_INT 4

/* The number of bytes in a long.  */
#define SIZEOF_LONG 4

/* The number of bytes in a long double.  */
#define SIZEOF_LONG_DOUBLE 12

/* The number of bytes in a short.  */
#define SIZEOF_SHORT 2

/* The number of bytes in a unsigned int.  */
#define SIZEOF_UNSIGNED_INT 4

/* The number of bytes in a unsigned long.  */
#define SIZEOF_UNSIGNED_LONG 4

/* The number of bytes in a unsigned short.  */
#define SIZEOF_UNSIGNED_SHORT 2

/* Define if you have the ANSI C header files.  */
#ifndef STDC_HEADERS
#define STDC_HEADERS 1
#endif

/* Define if you have the <errno.h> header file.  */
#ifndef HAVE_ERRNO_H
#define HAVE_ERRNO_H 1
#endif

/* Define if you have the <fcntl.h> header file.  */
#ifndef HAVE_FCNTL_H
#define HAVE_FCNTL_H 1
#endif

/* Define if you have the <limits.h> header file.  */
#ifndef HAVE_LIMITS_H
#define HAVE_LIMITS_H 1
#endif

/* Name of package */
#define PACKAGE "lame"

/* Define if compiler has function prototypes */
#define PROTOTYPES 1

/* faster log implementation with less but enough precission */
#define USE_FAST_LOG 1

#ifndef HAVE_STRCHR
#define HAVE_STRCHR 1
#endif

#ifndef HAVE_MEMCPY
#define HAVE_MEMCPY 1
#endif

#include <stdint.h>

typedef long double ieee854_float80_t;
typedef double      ieee754_float64_t;
typedef float       ieee754_float32_t;

#ifdef HAVE_MPGLIB
# define DECODE_ON_THE_FLY 1
#endif

#ifdef LAME_ACM
/* memory hacking for driver purposes */
#define calloc(x,y) acm_Calloc(x,y)
#define free(x)     acm_Free(x)
#define malloc(x)   acm_Malloc(x)

#include <stddef.h>
void *acm_Calloc( size_t num, size_t size );
void *acm_Malloc( size_t size );
void acm_Free( void * mem);
#endif /* LAME_ACM */

#define LAME_LIBRARY_BUILD

#endif