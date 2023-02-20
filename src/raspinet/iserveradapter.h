#ifndef NET_ISERVERADAPTER_H
#define NET_ISERVERADAPTER_H

#ifndef UNUSED
#define UNUSED(v) ((void)(v))
#endif

namespace net {

class IServerAdapter {
friend class Connection;
friend class TCPConnection;
public:
// ����packet�ص�
virtual IPacketHandler::HPRetCode handlePacket(Connection *connection, Packet *packet) = 0;
// ����packet�ص�
virtual bool handleBatchPacket(Connection *connection, PacketQueue &packetQueue) {
UNUSED(packetQueue);
UNUSED(connection);
return false;
}
// ���캯��
IServerAdapter() {
_batchPushPacket = false;
}
// ��������
virtual ~IServerAdapter() {}
// setBatch()
void setBatchPushPacket(bool value) {
_batchPushPacket = value;
}
private:
bool _batchPushPacket;          // ����post packet
};
}

#endif /*ISERVERADAPTER_H*/