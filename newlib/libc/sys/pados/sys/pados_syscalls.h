#pragma once

#include <sys/types.h>
#include <sys/pados_types.h>

#ifdef __cplusplus
extern "C" {
#endif

int sys_open(const char* path, int flags);
int sys_close(int file);
int sys_dup(int oldFile);
int sys_fstat(int file, struct stat* buf);
int sys_stat(const char* path, struct stat* buf);
int sys_isatty(int file);
off_t sys_lseek(int file, off_t offset, int whence);
ssize_t sys_read(int file, void* buffer, size_t length);
ssize_t sys_write(int file, const void* buffer, size_t length);
int sys_kill(pid_t pid, int sig);
pid_t sys_getpid(void);
caddr_t sys_sbrk(ptrdiff_t size);
bigtime_t sys_get_real_time();

#ifdef __cplusplus
}
#endif
