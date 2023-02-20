#ifndef NET_CONNECTION_H_
#define NET_CONNECTION_H_

#define READ_WRITE_SIZE 8192
#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

namespace net {

class Connection {

public:
Connection(Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

virtual ~Connection();

void setServer(bool isServer) {
_isServer = isServer;
}

void setIOComponent(IOComponent *ioc) {
_iocomponent = ioc;
}

IOComponent *getIOComponent() {
return _iocomponent;
}
void setDefaultPacketHandler(IPacketHandler *ph) {
_defaultPacketHandler = ph;
}

bool postPacket(Packet *packet, IPacketHandler *packetHandler = NULL, void *args = NULL, bool noblocking = true);

bool handlePacket(DataBuffer *input, PacketHeader *header);

bool checkTimeout(int64_t now);

virtual bool writeData() = 0;

virtual bool readData() = 0;

virtual void setWriteFinishClose(bool v) {
UNUSED(v);
}

void setQueueTimeout(int queueTimeout) {
_queueTimeout = queueTimeout;
}

virtual void clearOutputBuffer() {
;
}

void setQueueLimit(int limit) {
_queueLimit = limit;
}

bool isConnectState();

uint64_t getServerId() {
if (_socket) {
return _socket->getId();
}
return 0;
}

uint64_t getPeerId() {
if (_socket) {
return _socket->getPeerId();
}
return 0;
}

int getLocalPort() {
if (_socket) {
return _socket->getLocalPort();
}
return -1;
}

protected:
void disconnect();

protected:
IPacketHandler *_defaultPacketHandler;  // connection��Ĭ�ϵ�packet handler
bool _isServer;                         // �Ƿ�������
IOComponent *_iocomponent;
Socket *_socket;                        // Socket���
IPacketStreamer *_streamer;             // Packet����
IServerAdapter *_serverAdapter;         // ������������

PacketQueue _outputQueue;               // ���Ͷ���
PacketQueue _inputQueue;                // ���Ͷ���
PacketQueue _myQueue;                   // ��write�д���ʱ��ʱ��
sys::CThreadCond _outputCond;         // ���Ͷ��е���������
ChannelPool _channelPool;               // channel pool
int _queueTimeout;                      // ���г�ʱʱ��
int _queueTotalSize;                    // �����ܳ���
int _queueLimit;                        // ���������, ����������ֵpost�����ͻᱻwait
};
}

#endif /*CONNECTION_H_*/