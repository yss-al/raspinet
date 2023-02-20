#include "net.h"

namespace net {
TCPAcceptor::TCPAcceptor(Transport *owner, Socket *socket,
IPacketStreamer *streamer, IServerAdapter *serverAdapter) : IOComponent(owner, socket) {
_streamer = streamer;
_serverAdapter = serverAdapter;
}

bool TCPAcceptor::init(bool isServer) {
_socket->setSoBlocking(false);
return ((ServerSocket*)_socket)->listen();
}

bool TCPAcceptor::handleReadEvent() {
Socket *socket;
while ((socket = ((ServerSocket*)_socket)->accept()) != NULL) {
//SYS_LOG(INFO, "�������ӽ���, fd: %d", socket->getSocketHandle());
// TCPComponent, �ڷ�������
TCPComponent *component = new TCPComponent(_owner, socket, _streamer, _serverAdapter);

if (!component->init(true)) {
delete component;
return true;
}

// ���뵽iocomponents�У���ע��ɶ���socketevent��
_owner->addComponent(component, true, false);
}

return true;
}

void TCPAcceptor::checkTimeout(int64_t now) {}
}