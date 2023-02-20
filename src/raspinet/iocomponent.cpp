#include "net.h"

namespace net {

IOComponent::IOComponent(Transport *owner, Socket *socket) {
assert(socket);
_owner = owner;
_socket = socket;
_socket->setIOComponent(this);
_socketEvent = NULL;
atomic_set(&_refcount, 0);
_state = NET_UNCONNECTED; // ��������
_autoReconn = false; // ��Ҫ�Զ�����
_prev = _next = NULL;
_lastUseTime = sys::CTimeUtil::getTime();
_inUsed = false;
}

IOComponent::~IOComponent() {
if (_socket) {
_socket->close();
delete _socket;
_socket = NULL;
}
}

Transport *IOComponent::getOwner()
{
return _owner;
}

}