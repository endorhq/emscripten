#define _BSD_SOURCE
#include <sys/uio.h>
#include <unistd.h>
#include "syscall.h"
#include "emscripten.h"

ssize_t preadv(int fd, const struct iovec *iov, int count, off_t ofs)
{
#if __EMSCRIPTEN__
	size_t num;
	emscripten_sleep(1000);
	if (__wasi_syscall_ret(__wasi_fd_pread(fd, (struct __wasi_iovec_t*)iov, count, ofs, &num))) {
		return -1;
	}
	return num;
#else
	return syscall_cp(SYS_preadv, fd, iov, count,
		(long)(ofs), (long)(ofs>>32));
#endif
}
