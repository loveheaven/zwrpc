#include <fcntl.h> 

namespace zwrpc {
int make_close_on_exec(int fd) {
    return fcntl(fd, F_SETFD, FD_CLOEXEC);
}
}