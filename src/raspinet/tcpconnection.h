#ifndef NET_TCPCONNECTION_H_
#define NET_TCPCONNECTION_H_

namespace net {

class TCPConnection : public Connection {

public:
TCPConnection(Socket *socket, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

~TCPConnection();

bool writeData();

bool readData();

void setWriteFinishClose(bool v) {
_writeFinishClose = v;
}

void clearOutputBuffer() {
_output.clear();
}

void clearInputBuffer() {
_input.clear();
}

void setDisconnState();

private:
DataBuffer _output;      // �����buffer
DataBuffer _input;       // �����buffer
PacketHeader _packetHeader; // �����packet header
bool _gotHeader;            // packet header�Ѿ�ȡ��
bool _writeFinishClose;     // д��Ͽ�
};

}

#endif /*TCPCONNECTION_H_*/