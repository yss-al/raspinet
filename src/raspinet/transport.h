#ifndef NET_TRANSPORT_H_
#define NET_TRANSPORT_H_

#include <sys/ptrace.h>

namespace net {

class Transport : public sys::Runnable {

public:
Transport();

~Transport();

bool start();

bool stop();

bool wait();

void run(sys::CThread *thread, void *arg);

IOComponent *listen(const char *spec, IPacketStreamer *streamer, IServerAdapter *serverAdapter);

Connection *connect(const char *spec, IPacketStreamer *streamer, bool autoReconn = false);

bool disconnect(Connection *conn);

void addComponent(IOComponent *ioc, bool readOn, bool writeOn);

void removeComponent(IOComponent *ioc);

bool* getStop();

private:
int parseAddr(char *src, char **args, int cnt);

void eventLoop(SocketEvent *socketEvent);

void timeoutLoop();

void destroy();

private:

EPollSocketEvent _socketEvent;      // ��дsocket�¼�
sys::CThread _readWriteThread;    // ��д�����߳�
sys::CThread _timeoutThread;      // ��ʱ����߳�
bool _stop;                         // �Ƿ�ֹͣ

IOComponent *_delListHead, *_delListTail;  // �ȴ�ɾ����IOComponent����
IOComponent *_iocListHead, *_iocListTail;   // IOComponent����
bool _iocListChanged;                       // IOComponent���ϱ��Ĺ�
int _iocListCount;
sys::CThreadMutex _iocsMutex;
};
}

#endif /*TRANSPORT_H_*/