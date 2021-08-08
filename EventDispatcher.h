#pragma once

#include "OSConfig.h"
#if defined(OS_MACOSX)
#include <sys/event.h> 
#elif defined(OS_LINUX)
#include <sys/epoll.h> 
#endif

namespace zwrpc {

// Dispatch edge-triggered events of file descriptors to consumers
// running in separate bthreads.
class EventDispatcher {
friend class Socket;
public:
    EventDispatcher();
    
    virtual ~EventDispatcher();

    
private:
    DISALLOW_COPY_AND_ASSIGN(EventDispatcher);

    

    // The epoll to watch events.
    int _epfd;

};

EventDispatcher& GetGlobalEventDispatcher(int fd);

} // namespace brpc


