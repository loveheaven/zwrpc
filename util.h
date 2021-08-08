#pragma once

namespace zwrpc {
// Make file descriptor |fd| automatically closed during exec()
// Returns 0 on success, -1 when error and errno is set (by fcntl)
/* 一般来说进程往往会调用fork函数来执行一个子进程，调用execve()执行其他程序，
这时候可能就导致子进程中存在一些无用的文件描述符问题。

父进程在fork函数的时候，子进程会拷贝跟父进程一样的地址空间，包括寄存器，文件描述符，堆，栈等。
在一开始，父进程与子进程的文件描述符指向的是系统文件表中的同一项(包括文件状态，和文件偏移量)。 
当我们用execve执行其他程序的时候，全新的程序会替换子进程中的地址空间，数据段，堆栈，
此时保存与父进程文件描述符也就不存在了，也无法进行关闭，这时候就需要FD_CLOEXEC, 
表示子进程在执行exec的时候，该文件描述符就需要进行关闭。 
*/
int make_close_on_exec(int fd);

}
