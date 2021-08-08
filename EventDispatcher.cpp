#include "EventDispatcher.h"
#include <gflags/gflags.h>
#include "logging.h"
#include "util.h"

namespace zwrpc {

DEFINE_int32(event_dispatcher_num, 1, "Number of event dispatcher");

DEFINE_bool(usercode_in_pthread, false, 
            "Call user's callback in pthreads, use bthreads otherwise");

EventDispatcher::EventDispatcher()
    : _epfd(-1)
{
    
#if defined(OS_LINUX)
    _epfd = epoll_create(1024 * 1024);
    if (_epfd < 0) {
        PLOG(FATAL) << "Fail to create epoll";
        return;
    }
#elif defined(OS_MACOSX)
    _epfd = kqueue();
    if (_epfd < 0) {
        LCritical ( "Fail to create kqueue");
        return;
    }
#else
    #error Not implemented
#endif
    CHECK_EQ(0, zwrpc::make_close_on_exec(_epfd));

    
}

EventDispatcher::~EventDispatcher() {
    
    if (_epfd >= 0) {
        close(_epfd);
        _epfd = -1;
    }
    
}
}