#include <sys/socket.h>
#include "syscall.h"
#include "emscripten.h"

ssize_t recvfrom(int fd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict alen)
{
	emscripten_sleep(1000);
	return socketcall_cp(recvfrom, fd, buf, len, flags, addr, alen);
}
