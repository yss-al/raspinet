#ifndef NET_TCPACCEPTOR_H_
#define NET_TCPACCEPTOR_H_

namespace net {

class TCPAcceptor : public IOComponent {

public:
TCPAcceptor(Transport *owner, Socket *socket,
IPacketStreamer *streamer, IServerAdapter *serverAdapter);

bool init(bool isServer = false);

bool handleReadEvent();

bool handleWriteEvent() {
return true;
}

void checkTimeout(int64_t now);

private:
IPacketStreamer *_streamer;      // ���ݰ�������
IServerAdapter  *_serverAdapter; // ������������
};
}

#endif /*TCPACCEPTOR_H_*/