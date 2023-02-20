#ifndef NET_PACKET_H_
#define NET_PACKET_H_

namespace net {

#define NET_PACKET_FLAG 0x414e4554  // ANET

class PacketHeader {
public:
uint32_t _chid;         // ͨ��ID
int _pcode;             // ���ݰ�����
int _dataLen;           // ���ݰ�body����(��ͷ��Ϣ��)
};

class Packet {
friend class PacketQueue;

public:
Packet();

virtual ~Packet();

void setChannelId(uint32_t chid) {
_packetHeader._chid = chid;
}

uint32_t getChannelId() const {
return _packetHeader._chid;
}

void setPCode(int pcode) {
_packetHeader._pcode = pcode;
}

int getPCode() const {
return _packetHeader._pcode;
}

PacketHeader *getPacketHeader() {
return &_packetHeader;
}

void setPacketHeader(PacketHeader *header) {
if (header) {
memcpy(&_packetHeader, header, sizeof(PacketHeader));
}
}

virtual void free() {
delete this;
}

virtual bool isRegularPacket() {
return true;
}

virtual bool encode(DataBuffer *output) = 0;

virtual bool decode(DataBuffer *input, PacketHeader *header) = 0;

int64_t getExpireTime() const {
return _expireTime;
}

void setExpireTime(int milliseconds);

void setChannel(Channel *channel);

Channel *getChannel() const {
return _channel;
}

Packet *getNext() const {
return _next;
}

protected:
PacketHeader _packetHeader; // ���ݰ���ͷ��Ϣ
int64_t _expireTime;        // ����ʱ��
Channel *_channel;

Packet *_next;              // ����packetqueue����
};

}

#endif /*PACKET_H_*/