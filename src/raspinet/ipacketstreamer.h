#ifndef NET_IPACKETSTREAMER_H_
#define NET_IPACKETSTREAMER_H_

namespace net {

class IPacketStreamer {

public:
IPacketStreamer() {
_factory = NULL;
_existPacketHeader = true;
}

IPacketStreamer(IPacketFactory *factory) {
_factory = factory;
_existPacketHeader = true;
}

virtual ~IPacketStreamer() {}

virtual bool getPacketInfo(DataBuffer *input, PacketHeader *header, bool *broken) = 0;

virtual Packet *decode(DataBuffer *input, PacketHeader *header) = 0;

virtual bool encode(Packet *packet, DataBuffer *output) = 0;

bool existPacketHeader() {
return _existPacketHeader;
}

protected:
IPacketFactory *_factory;   // ����packet
bool _existPacketHeader;    // �Ƿ���packet header, ��http���Լ�Э��Ͳ���Ҫ���ͷ��Ϣ
};
}

#endif /*RUNNABLE_H_*/