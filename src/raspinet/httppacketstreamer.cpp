#include "net.h"

namespace net {
HttpPacketStreamer::HttpPacketStreamer() {
_httpPacketCode = 1;
_existPacketHeader = false; // 不要输出头信息
}

HttpPacketStreamer::HttpPacketStreamer(IPacketFactory *factory) : DefaultPacketStreamer(factory) {
_httpPacketCode = 1;
_existPacketHeader = false; // 不要输出头信息
}

bool HttpPacketStreamer::getPacketInfo(DataBuffer *input, PacketHeader *header, bool *broken) {
if (input->getDataLen() == 0) {
return false;
}
char *data = input->getData();
int cmplen = input->getDataLen();
if (cmplen > 4) cmplen = 4;
if (memcmp(data, "GET ", cmplen)) {
*broken = true;
return false;
}

int nr = input->findBytes("\r\n\r\n", 4);
if (nr < 0) {
return false;
}

header->_pcode = _httpPacketCode;
header->_chid = 0;
header->_dataLen = nr + 4;
return true;
}

}


