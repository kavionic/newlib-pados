#pragma once

#include <stddef.h>
#include <inttypes.h>

typedef int      handle_id;
typedef int      thread_id;
typedef int      sem_id;
typedef int      port_id;
typedef int      handler_id;
typedef int      tls_id;
typedef int      fs_id;
typedef int64_t  bigtime_t;
typedef int      status_t;
typedef int64_t  off64_t;
typedef uint64_t size64_t;
typedef int64_t  ssize64_t;

typedef uint16_t wchar16_t;

#ifdef __cplusplus
constexpr
#else
static const
#endif
handler_id	INVALID_HANDLE = -1;

#ifdef __cplusplus
constexpr
#else
static const
#endif
size_t		INVALID_INDEX = (size_t)-1;


