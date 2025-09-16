#ifndef _MACHINE__TYPES_H
#define	_MACHINE__TYPES_H

#include <machine/_default_types.h>

typedef	__int32_t	__blkcnt_t;
#define	__machine_blkcnt_t_defined

typedef	__int32_t	__blksize_t;
#define	__machine_blksize_t_defined

typedef	__uint64_t	__dev_t;
#define	__machine_dev_t_defined

typedef	__int64_t	_off_t;
#define	__machine_off_t_defined

typedef	_off_t		_fpos_t;
#define	__machine_fpos_t_defined

typedef	__uint64_t	__ino_t;
#define	__machine_ino_t_defined

typedef	__uint32_t	__mode_t;
#define	__machine_mode_t_defined

typedef	__uint64_t	_CLOCK_T_;
#define	__machine_clock_t_defined

typedef	int		_CLOCKID_T_;
#define	__machine_clockid_t_defined

typedef	__int64_t	__daddr_t;
#define	__machine_daddr_t_defined

typedef struct timespec timespec_t;
#define __timespec_t_defined

typedef struct timespec timestruc_t;
#define __timestruc_t_defined

#endif /* _MACHINE__TYPES_H */
