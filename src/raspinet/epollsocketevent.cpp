#include "net.h"

namespace net {

EPollSocketEvent::EPollSocketEvent() {
_iepfd = epoll_create(MAX_SOCKET_EVENTS);
}

EPollSocketEvent::~EPollSocketEvent() {
close(_iepfd);
}

bool EPollSocketEvent::addEvent(Socket *socket, bool enableRead, bool enableWrite) {

struct epoll_event ev;
memset(&ev, 0, sizeof(ev));
ev.data.ptr = socket->getIOComponent();
// ����Ҫ������¼�����
ev.events = 0;

if (enableRead) {
ev.events |= EPOLLIN;
}
if (enableWrite) {
ev.events |= EPOLLOUT;
}

//_mutex.lock();
bool rc = (epoll_ctl(_iepfd, EPOLL_CTL_ADD, socket->getSocketHandle(), &ev) == 0);
//_mutex.unlock();
//SYS_LOG(ERROR, "EPOLL_CTL_ADD: %d => %d,%d, %d", socket->getSocketHandle(), enableRead, enableWrite, pthread_self());
return rc;
}

bool EPollSocketEvent::setEvent(Socket *socket, bool enableRead, bool enableWrite) {

struct epoll_event ev;
memset(&ev, 0, sizeof(ev));
ev.data.ptr = socket->getIOComponent();
// ����Ҫ������¼�����
ev.events = 0;

if (enableRead) {
ev.events |= EPOLLIN;
}
if (enableWrite) {
ev.events |= EPOLLOUT;
}

//_mutex.lock();
bool rc = (epoll_ctl(_iepfd, EPOLL_CTL_MOD, socket->getSocketHandle(), &ev) == 0);
//_mutex.unlock();
//SYS_LOG(ERROR, "EPOLL_CTL_MOD: %d => %d,%d, %d", socket->getSocketHandle(), enableRead, enableWrite, pthread_self());
return rc;
}

bool EPollSocketEvent::removeEvent(Socket *socket) {

struct epoll_event ev;
memset(&ev, 0, sizeof(ev));
ev.data.ptr = socket->getIOComponent();
// ����Ҫ������¼�����
ev.events = 0;
//_mutex.lock();
bool rc = (epoll_ctl(_iepfd, EPOLL_CTL_DEL, socket->getSocketHandle(), &ev) == 0);
//_mutex.unlock();
//SYS_LOG(ERROR, "EPOLL_CTL_DEL: %d", socket->getSocketHandle());
return rc;
}

int EPollSocketEvent::getEvents(int timeout, IOEvent *ioevents, int cnt) {

struct epoll_event events[MAX_SOCKET_EVENTS];

if (cnt > MAX_SOCKET_EVENTS) {
cnt = MAX_SOCKET_EVENTS;
}

int res = epoll_wait(_iepfd, events, cnt , timeout);

// ��ʼ��
if (res > 0) {
memset(ioevents, 0, sizeof(IOEvent) * res);
}

// ��events���¼�ת����IOEvent���¼�
for (int i = 0; i < res; i++) {
ioevents[i]._ioc = (IOComponent*)events[i].data.ptr;
if (events[i].events & (EPOLLERR | EPOLLHUP)) {
ioevents[i]._errorOccurred = true;
}
if ((events[i].events & EPOLLIN) != 0) {
ioevents[i]._readOccurred = true;
}
if ((events[i].events & EPOLLOUT) != 0) {
ioevents[i]._writeOccurred = true;
}
}

return res;
}
}